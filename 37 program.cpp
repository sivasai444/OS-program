#include <stdio.h>
#include <stdlib.h>

// Function to simulate FCFS disk scheduling
void fcfsDiskScheduling(int requests[], int numRequests, int initialPosition) {
    int totalMovement = 0;
    int currentHeadPosition = initialPosition;

    printf("Sequence of disk head movements:\n");

    for (int i = 0; i < numRequests; i++) {
        int distance = abs(requests[i] - currentHeadPosition);
        totalMovement += distance;

        printf("Move from %d to %d (Distance: %d)\n", currentHeadPosition, requests[i], distance);

        currentHeadPosition = requests[i];
    }

    printf("Total head movement: %d\n", totalMovement);
}

int main() {
    // Example disk requests
    int diskRequests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int numRequests = sizeof(diskRequests) / sizeof(diskRequests[0]);
    int initialHeadPosition = 53; // Initial position of disk head

    // Simulate FCFS disk scheduling
    fcfsDiskScheduling(diskRequests, numRequests, initialHeadPosition);

    return 0;
}
