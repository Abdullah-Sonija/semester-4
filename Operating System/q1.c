#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define READERS 5
#define WRITERS 2

int research_document = 0;

sem_t resource;      // Controls access to shared resource
sem_t serviceQueue;  // Fairness queue

pthread_mutex_t rmutex;

int readCount = 0;

void *reader(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        sem_wait(&serviceQueue);
        pthread_mutex_lock(&rmutex);
        readCount++;
        if (readCount == 1)
        {
            sem_wait(&resource);
        }
        pthread_mutex_unlock(&rmutex);
        sem_post(&serviceQueue);
        printf("Reader %d is reading document value = %d\n",id, research_document);
        sleep(rand() % 3 + 1);
        pthread_mutex_lock(&rmutex);
        readCount--;
        if (readCount == 0)
        {
            sem_post(&resource);
        }
        pthread_mutex_unlock(&rmutex);
        printf("Reader %d finished reading\n", id);
        sleep(rand() % 3 + 1);
    }
}

void *writer(void *arg)
{
    int id = *(int *)arg;
    while (1)
    {
        sem_wait(&serviceQueue);
        sem_wait(&resource);
        sem_post(&serviceQueue);
        research_document++;
        printf("Writer %d updated document to %d\n",id, research_document);
        sleep(rand() % 3 + 1);
        printf("Writer %d finished writing\n", id);
        sem_post(&resource);
        sleep(rand() % 4 + 1);
    }
}

int main()
{
    pthread_t r[READERS], w[WRITERS];
    int rid[READERS];
    int wid[WRITERS];
    sem_init(&resource, 0, 1);
    sem_init(&serviceQueue, 0, 1);
    pthread_mutex_init(&rmutex, NULL);
    for (int i = 0; i < READERS; i++)
    {
        rid[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &rid[i]);
    }
    for (int i = 0; i < WRITERS; i++)
    {
        wid[i] = i + 1;
        pthread_create(&w[i], NULL, writer, &wid[i]);
    }
    for (int i = 0; i < READERS; i++)
    {
        pthread_join(r[i], NULL);
    }
    for (int i = 0; i < WRITERS; i++)
    {
        pthread_join(w[i], NULL);
    }
    sem_destroy(&resource);
    sem_destroy(&serviceQueue);
    pthread_mutex_destroy(&rmutex);
    return 0;
}
