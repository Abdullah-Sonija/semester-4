#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define PRODUCERS 4
#define CONSUMERS 3

int buffer[BUFFER_SIZE];

int in = 0;
int out = 0;

sem_t empty;
sem_t full;

pthread_mutex_t mutex;

int order_id = 1;

void *producer(void *arg)
{
    int id = *(int *)arg;
    while (1)
    {
        sleep(rand() % 3 + 1);
        int order = order_id++;
        printf("Customer %d wants to place Order %d\n",id, order);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = order;
        printf("Customer %d placed Order %d at slot %d\n",id, order, in);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg)
{
    int id = *(int *)arg;
    while (1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int order = buffer[out];
        printf("Delivery Agent %d picked Order %d from slot %d\n",id, order, out);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        printf("Delivery Agent %d delivering Order %d\n",id, order);
        sleep(rand() % 5 + 1);
        printf("Delivery Agent %d completed Order %d\n",
               id, order);
    }
}

int main()
{
    pthread_t prod[PRODUCERS];
    pthread_t cons[CONSUMERS];
    int pid[PRODUCERS];
    int cid[CONSUMERS];
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < PRODUCERS; i++)
    {
        pid[i] = i + 1;
        pthread_create(&prod[i],NULL,producer,&pid[i]);
    }
    for (int i = 0; i < CONSUMERS; i++)
    {
        cid[i] = i + 1;
        pthread_create(&cons[i],NULL,consumer,&cid[i]);
    }
    for (int i = 0; i < PRODUCERS; i++)
    {
        pthread_join(prod[i], NULL);
    }
    for (int i = 0; i < CONSUMERS; i++)
    {
        pthread_join(cons[i], NULL);
    }
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
