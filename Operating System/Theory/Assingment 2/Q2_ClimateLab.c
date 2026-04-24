#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define N 1000
#define NUM_TILES 100
#define TILE_SIZE 10
#define T_HOT 35.0
#define T_COLD -10.0

double matrix[N][N];
double risk_matrix[N][N];
int hotspot_count = 0;
int coldspot_count = 0;
int anomaly_count = 0;
double global_max = -1000.0, global_min = 1000.0, global_sum = 0.0;

pthread_mutex_t global_stats_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t hotspot_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t coldspot_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_barrier_t sync_barrier;

typedef struct {
    int start_row;
    int end_row;
} TileData;

void *process_tile(void *arg) {
    TileData *data = (TileData *)arg;
    double local_max = -1000.0, local_min = 1000.0, local_sum = 0.0;
    int count = (data->end_row - data->start_row) * N;

    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < N; j++) {
            double val = matrix[i][j];
            if (val > local_max) local_max = val;
            if (val < local_min) local_min = val;
            local_sum += val;
        }
    }

    double local_mean = local_sum / count;
    int local_anomalies = 0;
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < N; j++) {
            if (fabs(matrix[i][j] - local_mean) > 20.0) {
                local_anomalies++;
            }
        }
    }
    pthread_mutex_lock(&global_stats_mutex);
    if (local_max > global_max) global_max = local_max;
    if (local_min < global_min) global_min = local_min;
    global_sum += local_sum;
    anomaly_count += local_anomalies;
    pthread_mutex_unlock(&global_stats_mutex);
    pthread_exit(NULL);
}

void *identify_hotspots(void *arg) {
    int local_count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] > T_HOT) local_count++;
        }
    }
    pthread_mutex_lock(&hotspot_mutex);
    hotspot_count += local_count;
    pthread_mutex_unlock(&hotspot_mutex);
    pthread_barrier_wait(&sync_barrier);
    pthread_exit(NULL);
}

void *identify_coldspots(void *arg) {
    int local_count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] < T_COLD) local_count++;
        }
    }
    pthread_mutex_lock(&coldspot_mutex);
    coldspot_count += local_count;
    pthread_mutex_unlock(&coldspot_mutex);
    pthread_barrier_wait(&sync_barrier);
    pthread_exit(NULL);
}

void *normalize_and_risk(void *arg) {
    pthread_barrier_wait(&sync_barrier);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Simplified normalization logic for simulation
            double norm = (matrix[i][j] - global_min) / (global_max - global_min + 0.001);
            risk_matrix[i][j] = norm * 1.5; 
        }
    }
    pthread_exit(NULL);
}


int main() {
    printf("Climate Lab Simulation Started...\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = ((rand() % 1000) / 10.0) - 20.0; // range -20 to 80
        }
    }
    pthread_t tiles[NUM_TILES];
    TileData tdata[NUM_TILES];
    int rows_per_thread = N / NUM_TILES;

    for (int i = 0; i < NUM_TILES; i++) {
        tdata[i].start_row = i * rows_per_thread;
        tdata[i].end_row = (i + 1) * rows_per_thread;
        pthread_create(&tiles[i], NULL, process_tile, &tdata[i]);
    }
    for (int i = 0; i < NUM_TILES; i++) {
        pthread_join(tiles[i], NULL);
    }
    double global_mean = global_sum / (N * N);
    printf("Data Phase Complete:\n Max Temp: %.2f, Min Temp: %.2f\n Mean: %.2f, Anomalies: %d\n", 
            global_max, global_min, global_mean, anomaly_count);
    pthread_barrier_init(&sync_barrier, NULL, 3);
    pthread_t t_hot, t_cold, t_norm;

    pthread_create(&t_hot, NULL, identify_hotspots, NULL);
    pthread_create(&t_cold, NULL, identify_coldspots, NULL);
    pthread_create(&t_norm, NULL, normalize_and_risk, NULL);

    pthread_join(t_hot, NULL);
    pthread_join(t_cold, NULL);
    pthread_join(t_norm, NULL);

    printf("\nTask Phase Complete:\n Hotspots Detected: %d\n Coldspots Detected: %d\n", 
           hotspot_count, coldspot_count);
           
    printf("\nSample Risk Matrix (5x5):\n");
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++) {
            printf("%.2f ", risk_matrix[i][j]);
        }
        printf("\n");
    }
    pthread_barrier_destroy(&sync_barrier);
    return 0;
}