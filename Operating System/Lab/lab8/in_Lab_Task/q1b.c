#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10000000
#define NUM_THREADS 10

float *a, *b, *c;

void *add_arrays(void *arg)
{
	long thread_id = (long) arg;

	long chunk_size = ARRAY_SIZE / NUM_THREADS;
	long start_index = thread_id * chunk_size;
	long end_index = start_index + chunk_size;

	for (long i = start_index; i < end_index; i++)
	{
		c[i] = a[i] + b[i];
	}
	pthread_exit(NULL);
}

int main()
{
	a = (float *)malloc(ARRAY_SIZE * sizeof(float));
	b = (float *)malloc(ARRAY_SIZE * sizeof(float));
	c = (float *)malloc(ARRAY_SIZE * sizeof(float));

	if (a == NULL || b == NULL || c == NULL)
	{
		printf("Memory allocation failed.");
		return 1;
	}
	for (long i = 0; i < ARRAY_SIZE; i++)
	{
		a[i] = i * 1.25;
		b[i] = i * 1.5;
	}
	pthread_t threads[NUM_THREADS];
    for (long i = 0; i< NUM_THREADS; i++)
    {
        pthread_create(&threads[i],NULL,add_arrays,(void *)i);
    }
	for ( long i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
	printf("Concurrent addition:\n");
	printf("c value at 1000: %.3f\n", c[1000]);
	printf("c value at 10: %.3f\n", c[10]);
	
	free(a);
	free(b);
	free(c);
	
	return 0;
}
