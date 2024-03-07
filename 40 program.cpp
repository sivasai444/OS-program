#include <stdio.h>
#include <sys/stat.h>

int main() {
    // Path to the file
    const char *filename = "example.txt";

    // Set read, write, and execute permissions for owner
    // Set read and execute permissions for group
    // Set read permission for others
    if (chmod(filename, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH) == 0) {
        printf("File permissions updated successfully.\n");
    } else {
        perror("Error updating file permissions");
    }

    return 0;
}
