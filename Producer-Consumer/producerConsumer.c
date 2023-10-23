// Producer Consumer Problem using Semaphores
// Filippo Ferrando

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
#define MAX_ITEMS 100

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int prod_cnt = 0;
int cons_cnt = 0;

sem_t mutex;
sem_t empty;
sem_t full;

void *producer(){
    int item = 1;

    while(prod_cnt < MAX_ITEMS){
        sem_wait(&empty);   // wait for empty buffer
        sem_wait(&mutex);   // wait for mutex

        buffer[in] = item;  // produce item
        printf("Produced item %d\n", item);
        item++;            // increment item
        in = (in + 1) % BUFFER_SIZE;    // increment in

        prod_cnt++;

        sem_post(&mutex);   // release mutex
        sem_post(&full);    // signal full buffer
    }
    pthread_exit(NULL);
}

void *consumer(){
    while(cons_cnt < MAX_ITEMS){
        sem_wait(&full);    // wait for full buffer
        sem_wait(&mutex);   // wait for mutex

        int item = buffer[out]; // consume item
        printf("Consumed item %d\n", item);
        out = (out + 1) % BUFFER_SIZE;  // increment out

        cons_cnt++;

        sem_post(&mutex);   // release mutex
        sem_post(&empty);   // signal empty buffer
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t prod, cons;

    sem_init(&mutex, 0, 1); // mutex = 1
    sem_init(&empty, 0, BUFFER_SIZE);   // empty = BUFFER_SIZE
    sem_init(&full, 0, 0);  // full = 0

    pthread_create(&prod, NULL, producer, NULL);    // create producer thread
    pthread_create(&cons, NULL, consumer, NULL);    // create consumer thread

    pthread_join(prod, NULL);   // wait for producer thread
    pthread_join(cons, NULL);   // wait for consumer thread

    sem_destroy(&mutex);    // destroy semaphores
    sem_destroy(&empty);    
    sem_destroy(&full);

    return 0;

}

