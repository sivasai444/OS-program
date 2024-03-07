#include <stdio.h>

#define MAX_BLOCKS 10

// Function to allocate memory using Worst Fit
void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_BLOCKS];

    for (int i = 0; i < n; i++) {
        allocation[i] = -1; // Initialize allocation array

        int worstFitIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstFitIndex == -1 || blockSize[j] > blockSize[worstFitIndex]) {
                    worstFitIndex = j;
                }
            }
        }

        if (worstFitIndex != -1) {
            allocation[i] = worstFitIndex;
            blockSize[worstFitIndex] -= processSize[i];
        }
    }

    // Display allocation details
    printf("\nProcess\t Process Size \t Block Index\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t %d\t\t ", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i]);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_BLOCKS];
    int m, n; // Number of memory blocks and processes

    // Input: Number of memory blocks
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);

    // Input: Memory block sizes
    printf("Enter the size of memory blocks:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    // Input: Number of processes
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    // Input: Process sizes
    printf("Enter the size of processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // Call Worst Fit algorithm
    worstFit(blockSize, m, processSize, n);

    return 0;
}
