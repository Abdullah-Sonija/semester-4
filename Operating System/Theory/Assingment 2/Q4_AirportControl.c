#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define MAX_FLIGHTS 100
#define TYPE_LANDING 1
#define TYPE_EMERGENCY 2
#define TYPE_TAKEOFF 3

typedef struct {
    int id;
    int type;
    time_t arrival_time;
    int priority;
} Flight;

Flight queue[MAX_FLIGHTS];
int queue_count = 0;
int runway_busy[2] = {0, 0};

pthread_mutex_t atc_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_flight_ready = PTHREAD_COND_INITIALIZER;

int extract_max_flight() {
    if (queue_count == 0) return -1;
    int max_idx = 0;
    for(int i = 1; i < queue_count; i++) {
        if(queue[i].priority > queue[max_idx].priority) {
            max_idx = i;
        }
    }
    // Remove from array by shifting
    int selected_id = queue[max_idx].id;
    for(int i = max_idx; i < queue_count - 1; i++) {
        queue[i] = queue[i+1];
    }
    queue_count--;
    return selected_id;
}

void *flight_generator(void *arg) {
    int f_id = 1;
    while (1) {
        pthread_mutex_lock(&atc_mutex);
        if (queue_count < MAX_FLIGHTS) {
            int type = (rand() % 3) + 1; 
            queue[queue_count].id = f_id++;
            queue[queue_count].type = type;
            queue[queue_count].arrival_time = time(NULL);
            queue[queue_count].priority = (type == TYPE_EMERGENCY) ? 100 : (type == TYPE_LANDING ? 50 : 10);
            
            char *t_name = type == TYPE_EMERGENCY ? "EMERGENCY" : (type == TYPE_LANDING ? "Landing" : "Takeoff");
            printf("[Generator] Flight %d added (%s)\n", f_id-1, t_name);
            queue_count++;
            pthread_cond_signal(&cond_flight_ready);
        }
        pthread_mutex_unlock(&atc_mutex);
        sleep(2);
    }
    return NULL;
}

void *runway_controller(void *arg) {
    int r_id = *(int *)arg;
    while (1) {
        pthread_mutex_lock(&atc_mutex);
        while (queue_count == 0) {
            pthread_cond_wait(&cond_flight_ready, &atc_mutex);
        }
        int flight_id = extract_max_flight();
        runway_busy[r_id] = 1;
        printf("[Runway %d] Cleared Flight %d. Runway active.\n", r_id, flight_id);
        pthread_mutex_unlock(&atc_mutex);
        sleep(3); 
        pthread_mutex_lock(&atc_mutex);
        runway_busy[r_id] = 0;
        printf("[Runway %d] Free.\n", r_id);
        pthread_mutex_unlock(&atc_mutex);
    }
    return NULL;
}

void *emergency_monitor(void *arg) {
    while (1) {
        pthread_mutex_lock(&atc_mutex);
        time_t current = time(NULL);
        for (int i = 0; i < queue_count; i++) {
            if (current - queue[queue_count].arrival_time > 5) {
                queue[i].priority += 5;
            }
            if (queue[i].type == TYPE_EMERGENCY) {
                printf("[EMERGENCY MONITOR] Preemption alert for Flight %d!\n", queue[i].id);
            }
        }
        pthread_mutex_unlock(&atc_mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    printf("Starting Airport Control Simulation...\n");
    pthread_t generator, monitor, r_threads[2];
    int r_ids[2] = {0, 1};
    pthread_create(&generator, NULL, flight_generator, NULL);
    pthread_create(&monitor, NULL, emergency_monitor, NULL);
    for (int i=0; i<2; i++) {
        pthread_create(&r_threads[i], NULL, runway_controller, &r_ids[i]);
    }
    sleep(20); 
    return 0;
}