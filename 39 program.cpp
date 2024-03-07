#include <stdio.h>
#include <stdlib.h>

// Function to simulate C-SCAN disk scheduling
void cScanDiskScheduling(int requests[], int numRequests, int initialPosition, int diskSize) {
    int totalMovement = 0;
    int currentHeadPosition = initialPosition;

    printf("Sequence of disk head movements:\n");

    // Sort the requests in ascending order
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                // Swap if out of order
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Move towards the right (increasing track numbers)
    for (int i = 0; i < numRequests; i++) {
        if (requests[i] >= currentHeadPosition) {
            int distance = requests[i] - currentHeadPosition;
            totalMovement += distance;

            printf("Move from %d to %d (Distance: %d)\n", currentHeadPosition, requests[i], distance);

            currentHeadPosition = requests[i];
        }
    }

    // Move to the right end
    totalMovement += diskSize - currentHeadPosition;
    printf("Move from %d to %d (Distance: %d)\n", currentHeadPosition, diskSize, diskSize - currentHeadPosition);

    // Move towards the left (decreasing track numbers) starting from 0
    totalMovement += diskSize;
    printf("Move from %d to 0 (Distance: %d)\n", diskSize, diskSize);

    for (int i = 0; i < numRequests; i++) {
        int distance = requests[i];
        totalMovement += distance;

        printf("Move from 0 to %d (Distance: %d)\n", requests[i], distance);

        currentHeadPosition = requests[i];
    }

    printf("Total head movement: %d\n", totalMovement);
}

int main() {
    // Example disk requests
    int diskRequests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int numRequests = sizeof(diskRequests) / sizeof(diskRequests[0]);
    int initialHeadPosition = 53; // Initial position of disk head
    int diskSize = 200; // Size of the disk

    // Simulate C-SCAN disk scheduling
    cScanDiskScheduling(diskRequests, numRequests, initialHeadPosition, diskSize);

    return 0;
}
