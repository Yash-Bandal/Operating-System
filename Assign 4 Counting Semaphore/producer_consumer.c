#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Size of the buffer

// Shared buffer and index variables for producer and consumer
int buffer[BUFFER_SIZE];
int in = 0;  // Index for the producer
int out = 0; // Index for the consumer

// Semaphores and mutex for synchronization
sem_t empty;         // Tracks empty slots in the buffer
sem_t full;          // Tracks filled slots in the buffer
pthread_mutex_t mutex; // Mutex to ensure mutual exclusion

// Producer function
void* producer(void* arg) {
    for (int i = 0; i < 10; i++) { // Produces 10 items
        sem_wait(&empty);               // Wait for an empty slot
        pthread_mutex_lock(&mutex);      // Enter critical section

        // Produce an item and place it in the buffer
        buffer[in] = i;
        printf("Produced: %d\n", buffer[in]);
        in = (in + 1) % BUFFER_SIZE;     // Update the producer index

        pthread_mutex_unlock(&mutex);    // Exit critical section
        sem_post(&full);                 // Signal that a new item is available
        sleep(1);                        // Simulate production time
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) { // Consumes 10 items
        sem_wait(&full);               // Wait for a filled slot
        pthread_mutex_lock(&mutex);     // Enter critical section

        // Consume an item from the buffer
        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;  // Update the consumer index

        pthread_mutex_unlock(&mutex);   // Exit critical section
        sem_post(&empty);               // Signal that a slot is now empty
        sleep(1);                       // Simulate consumption time
    }
    return NULL;
}

int main() {
    // Thread variables for producer and consumer
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Start with all slots empty
    sem_init(&full, 0, 0);            // Start with no filled slots
    pthread_mutex_init(&mutex, NULL);  // Initialize mutex

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for both threads to complete
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Clean up resources
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

// gcc producer_consumer.c -lpthread
// ./a.out

//oe gcc -o producer_consumer producer_consumer.c -lpthread
//./producer_consumer


    
