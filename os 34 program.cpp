#include <stdio.h>
#include <stdlib.h>

// Define a structure for a record
struct Record {
    int id;
    char name[50];
    float salary;
};

// Function to write records to a file
void writeRecordToFile(const char *filename, struct Record *record) {
    FILE *file = fopen(filename, "ab");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fwrite(record, sizeof(struct Record), 1, file);

    fclose(file);
}

// Function to read records from a file sequentially
void readRecordsFromFile(const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    struct Record record;

    while (fread(&record, sizeof(struct Record), 1, file) == 1) {
        printf("ID: %d\nName: %s\nSalary: %.2f\n\n", record.id, record.name, record.salary);
    }

    fclose(file);
}

int main() {
    // Example records
    struct Record records[] = {
        {1, "John Doe", 50000.0},
        {2, "Jane Smith", 60000.0},
        {3, "Bob Johnson", 70000.0}
    };

    int numRecords = sizeof(records) / sizeof(records[0]);

    const char *filename = "sequential_records.dat";

    // Write records to the file
    for (int i = 0; i < numRecords; i++) {
        writeRecordToFile(filename, &records[i]);
    }

    // Read and display records from the file
    readRecordsFromFile(filename);

    return 0;
}
