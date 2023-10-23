#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define EATING_TIME 2
#define THINKING_TIME 1

pthread_t philosophers[NUM_PHILOSOPHERS]; // Threads
sem_t forks[NUM_PHILOSOPHERS];            // Semaphores

void *philosopher(void *arg) {  
    int id = *((int *)arg); // Get philosopher id
    int left_fork = id; 
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;   

    while (1) {
        printf("Philosopher %d thinking\n", id);    
        sleep(THINKING_TIME);

        printf("Philosopher %d want to eat\n", id); 
        sem_wait(&forks[left_fork]);    
        sem_wait(&forks[right_fork]);

        printf("Philosopher %d eating\n", id);  
        sleep(EATING_TIME);

        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);

        printf("Philosopher %d finished eating\n", id);
    }
}

int main() {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }

    int philosopher_ids[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}