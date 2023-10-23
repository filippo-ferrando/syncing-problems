#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t rw_mutex, mutex;
int data = 0;
int readers_count = 0;

void *reader(void *arg) {
    while (1) {
        sleep(1); // Reading simulation
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        printf("Reader %d has read: %d\n", *((int *)arg), data);

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);
    }
}

void *writer(void *arg) {
    while (1) {
        sleep(1); // Wrting simulation
        sem_wait(&rw_mutex);
        data++;
        printf("Writer %d has writed: %d\n", *((int *)arg), data);
        sem_post(&rw_mutex);
    }
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <num_readers> <num_writers>\n", argv[0]);
        return 1;
    }

    int n_readers = atoi(argv[1]);
    int n_writers = atoi(argv[2]);

    pthread_t readers[n_readers];
    pthread_t writers[n_writers];

    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    int reader_ids[n_readers];
    int writer_ids[n_writers];

    for (int i = 0; i < n_readers; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < n_writers; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < n_readers; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < n_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}