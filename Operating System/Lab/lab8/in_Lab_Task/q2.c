#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *array;
    int size;
} ThreadData;

void *calculate_average(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int sum = 0;
    
    for (int i = 0; i < data->size; i++) {
        sum += data->array[i];
    }
    
    int *average = malloc(sizeof(int));
    *average = sum / data->size; 
    
    pthread_exit((void *)average);
}

// Thread 2: Calculates Maximum
void *calculate_maximum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int max = data->array[0];
    
    for (int i = 1; i < data->size; i++) {
        if (data->array[i] > max) {
            max = data->array[i];
        }
    }
    
    int *max_val = malloc(sizeof(int));
    *max_val = max;
    
    pthread_exit((void *)max_val);
}

// Thread 3: Calculates Minimum
void *calculate_minimum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int min = data->array[0];
    
    for (int i = 1; i < data->size; i++) {
        if (data->array[i] < min) {
            min = data->array[i];
        }
    }
    
    int *min_val = malloc(sizeof(int));
    *min_val = min;
    
    pthread_exit((void *)min_val);
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    int size = argc - 1;
    int *numbers = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++){
        numbers[i] = atoi(argv[i+1]);
    }

    ThreadData data = {numbers, size};

    pthread_t thread_avg, thread_max, thread_min;
    void *result_avg, *result_max, *result_min;

    pthread_create(&thread_avg, NULL, calculate_average, (void *)&data);
    pthread_create(&thread_max, NULL, calculate_maximum, (void *)&data);
    pthread_create(&thread_min, NULL, calculate_minimum, (void *)&data);

    pthread_join(thread_avg, &result_avg);
    pthread_join(thread_max, &result_max);
    pthread_join(thread_min, &result_min);

    printf("The average value is %d.\n", *(int *)result_avg);
    printf("The minimum value is %d.\n", *(int *)result_min);
    printf("The maximum value is %d.\n", *(int *)result_max);

    free(result_avg);
    free(result_max);
    free(result_min);
    free(numbers);

    return 0;
}
