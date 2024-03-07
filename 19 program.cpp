#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2
#define MAX_COUNT 100000

// Shared data
int sharedCounter = 0;
pthread_mutex_t mutex;

// Function to be executed by each thread
void *threadFunction(void *arg) {
    for (int i = 0; i < MAX_COUNT; i++) {
        // Acquire the mutex lock before entering the critical section
        pthread_mutex_lock(&mutex);

        // Critical section: Access and modify the shared variable
        sharedCounter++;
        printf("Thread %ld: %d\n", (long)arg, sharedCounter);

        // Release the mutex lock after exiting the critical section
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIds[NUM_THREADS];

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, (void *)(long)i);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
