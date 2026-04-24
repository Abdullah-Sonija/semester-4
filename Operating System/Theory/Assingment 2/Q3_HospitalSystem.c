#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define CRITICAL 0
#define SERIOUS 1
#define NORMAL 2

int queue[3] = {0, 0, 0}; 

pthread_mutex_t hospital_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_doc_available = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_patient_waiting = PTHREAD_COND_INITIALIZER;


void *doctor_thread(void *arg) {
    int doc_id = *(int *)arg;
    int is_senior = (doc_id % 2 == 0); 
    int consecutive_normal = 0;

    while (1) {
        pthread_mutex_lock(&hospital_mutex);
        // Wait for patients
        while (queue[CRITICAL] == 0 && queue[SERIOUS] == 0 && queue[NORMAL] == 0) {
            pthread_cond_wait(&cond_patient_waiting, &hospital_mutex);
        }

        if (queue[SERIOUS] >= 5) {
            queue[SERIOUS]--;
            queue[CRITICAL]++;
            printf("[Doc %d] Promoted a Serious patient to Critical!\n", doc_id);
        }
        int treating = -1;
        if (queue[CRITICAL] > 0 && is_senior) {
            queue[CRITICAL]--; treating = CRITICAL; consecutive_normal = 0;
        } else if (queue[SERIOUS] > 0) {
            queue[SERIOUS]--; treating = SERIOUS; consecutive_normal = 0;
        } else if (queue[NORMAL] > 0 && consecutive_normal < 3) {
            queue[NORMAL]--; treating = NORMAL; consecutive_normal++;
        } else if (queue[NORMAL] > 0 && consecutive_normal >= 3) {
            if (queue[SERIOUS] == 0) {
                printf("[Doc %d] Force idle (needs Serious pt due to rule 4).\n", doc_id);
                pthread_cond_wait(&cond_patient_waiting, &hospital_mutex);
                pthread_mutex_unlock(&hospital_mutex);
                continue;
            }
        }
        pthread_mutex_unlock(&hospital_mutex);
        if (treating != -1) {
            char *p_types[] = {"Critical", "Serious", "Normal"};
            char *d_type = is_senior ? "Senior" : "Junior";
            printf("[%s Doc %d] Treating %s patient.\n", d_type, doc_id, p_types[treating]);
            sleep(1); 
        }
    }
    return NULL;
}

void *patient_generator(void *arg) {
    while (1) {
        int pt_type = rand() % 3;
        char *p_types[] = {"Critical", "Serious", "Normal"};

        pthread_mutex_lock(&hospital_mutex);
        queue[pt_type]++;
        printf("[System] %s Patient arrived. Queues: [C:%d, S:%d, N:%d]\n", 
               p_types[pt_type], queue[CRITICAL], queue[SERIOUS], queue[NORMAL]);
        pthread_cond_broadcast(&cond_patient_waiting);
        pthread_mutex_unlock(&hospital_mutex);
        sleep(1); 
    }
    return NULL;
}

int main() {
    pthread_t generator;
    pthread_t doctors[3];
    int doc_ids[3] = {0, 1, 2}; // 0 & 2 Senior, 1 Junior
    printf("Starting Smart Hospital Simulation...\n");
    pthread_create(&generator, NULL, patient_generator, NULL);
    for (int i = 0; i < 3; i++) {
        pthread_create(&doctors[i], NULL, doctor_thread, &doc_ids[i]);
    }
    sleep(15); 
    return 0;
}