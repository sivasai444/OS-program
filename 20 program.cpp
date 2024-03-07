#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, writeMutex;
int readCount = 0;

// Function prototypes
void *reader(void *arg);
void *writer(void *arg);

int main() {
    pthread_t readerThreads[NUM_READERS];
    pthread_t writerThreads[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&writeMutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&readerThreads[i], NULL, reader, (void *)(long)i);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writerThreads[i], NULL, writer, (void *)(long)i);
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readerThreads[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writerThreads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&writeMutex);

    return 0;
}

void *reader(void *arg) {
    int readerId = (int)(long)arg;

    while (1) {
        // Entry section
        sem_wait(&mutex);
        readCount++;

        // If the first reader, lock writeMutex
        if (readCount == 1) {
            sem_wait(&writeMutex);
        }

        // Exit section
        sem_post(&mutex);

        // Critical section: Reading
        printf("Reader %d is reading...\n", readerId);
        usleep(1000000); // Simulate reading time

        // Entry section
        sem_wait(&mutex);
        readCount--;

        // If the last reader, unlock writeMutex
        if (readCount == 0) {
            sem_post(&writeMutex);
        }

        // Exit section
        sem_post(&mutex);

        usleep(500000); // Sleep to simulate delay between read operations
    }

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writerId = (int)(long)arg;

    while (1) {
        // Entry section
        sem_wait(&writeMutex);

        // Critical section: Writing
        printf("Writer %d is writing...\n", writerId);
        usleep(1500000); // Simulate writing time

        // Exit section
        sem_post(&writeMutex);

        usleep(1000000); // Sleep to simulate delay between write operations
    }

    pthread_exit(NULL);
}
