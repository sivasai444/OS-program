#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3

// Function to find the optimal page to replace
int findOptimalPage(int frames[], int pageArray[], int currentPageIndex, int n) {
    int res = -1, farthest = currentPageIndex;
    for (int i = 0; i < MAX_FRAMES; i++) {
        int j;
        for (j = currentPageIndex; j < n; j++) {
            if (frames[i] == pageArray[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

// Function to simulate optimal paging
void optimalPageReplacement(int pageArray[], int n) {
    int frames[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        int currentPage = pageArray[i];

        int found = 0;
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == currentPage) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int replaceIndex = findOptimalPage(frames, pageArray, i + 1, n);
            frames[replaceIndex] = currentPage;
            pageFaults++;
        }

        // Display current state of frames
        printf("Frames: ");
        for (int j = 0; j < MAX_FRAMES; j++)
            printf("%d\t", frames[j]);
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pageArray[] = {1, 3, 0, 3, 5, 6, 3};
    int n = sizeof(pageArray) / sizeof(pageArray[0]);

    optimalPageReplacement(pageArray, n);

    return 0;
}
