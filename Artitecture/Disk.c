#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SECTOR_SIZE 512
#define NUM_SECTORS 1024
#define MAX_FILES 256
#define MAX_FILENAME 32

typedef struct {
    char name[MAX_FILENAME];
    int start_sector;
    int num_sectors;
} File;

typedef struct {
    unsigned char* data;
    bool* sector_map;
    File* file_table;
    int num_files;
} Disk;

// Initialize the disk
Disk* init_disk() {
    Disk* disk = (Disk*)malloc(sizeof(Disk));
    if (disk == NULL) {
        fprintf(stderr, "Failed to allocate disk structure\n");
        return NULL;
    }

    disk->data = (unsigned char*)calloc(NUM_SECTORS * SECTOR_SIZE, sizeof(unsigned char));
    disk->sector_map = (bool*)calloc(NUM_SECTORS, sizeof(bool));
    disk->file_table = (File*)calloc(MAX_FILES, sizeof(File));
    disk->num_files = 0;

    if (disk->data == NULL || disk->sector_map == NULL || disk->file_table == NULL) {
        fprintf(stderr, "Failed to allocate disk memory\n");
        free(disk->data);
        free(disk->sector_map);
        free(disk->file_table);
        free(disk);
        return NULL;
    }

    return disk;
}

// Free the disk
void free_disk(Disk* disk) {
    if (disk != NULL) {
        free(disk->data);
        free(disk->sector_map);
        free(disk->file_table);
        free(disk);
    }
}

// Find free sectors
int find_free_sectors(Disk* disk, int num_sectors) {
    int start = -1;
    int count = 0;

    for (int i = 0; i < NUM_SECTORS; i++) {
        if (!disk->sector_map[i]) {
            if (start == -1) start = i;
            count++;
            if (count == num_sectors) return start;
        } else {
            start = -1;
            count = 0;
        }
    }

    return -1; // Not enough contiguous free sectors
}

// Write file to disk
bool write_file(Disk* disk, const char* filename, const unsigned char* data, int size) {
    if (disk->num_files >= MAX_FILES) {
        fprintf(stderr, "File table full\n");
        return false;
    }

    int num_sectors = (size + SECTOR_SIZE - 1) / SECTOR_SIZE;
    int start_sector = find_free_sectors(disk, num_sectors);

    if (start_sector == -1) {
        fprintf(stderr, "Not enough free space on disk\n");
        return false;
    }

    // Update file table
    File* file = &disk->file_table[disk->num_files++];
    strncpy(file->name, filename, MAX_FILENAME - 1);
    file->name[MAX_FILENAME - 1] = '\0';
    file->start_sector = start_sector;
    file->num_sectors = num_sectors;

    // Write data to disk
    for (int i = 0; i < num_sectors; i++) {
        int bytes_to_write = (i == num_sectors - 1) ? size % SECTOR_SIZE : SECTOR_SIZE;
        if (bytes_to_write == 0) bytes_to_write = SECTOR_SIZE;
        memcpy(&disk->data[(start_sector + i) * SECTOR_SIZE], &data[i * SECTOR_SIZE], bytes_to_write);
        disk->sector_map[start_sector + i] = true;
    }

    return true;
}

// Read file from disk
unsigned char* read_file(Disk* disk, const char* filename, int* size) {
    for (int i = 0; i < disk->num_files; i++) {
        if (strcmp(disk->file_table[i].name, filename) == 0) {
            File* file = &disk->file_table[i];
            *size = file->num_sectors * SECTOR_SIZE;
            unsigned char* data = (unsigned char*)malloc(*size);
            if (data == NULL) {
                fprintf(stderr, "Failed to allocate memory for file read\n");
                return NULL;
            }
            memcpy(data, &disk->data[file->start_sector * SECTOR_SIZE], *size);
            return data;
        }
    }
    fprintf(stderr, "File not found\n");
    return NULL;
}

// Delete file from disk
bool delete_file(Disk* disk, const char* filename) {
    for (int i = 0; i < disk->num_files; i++) {
        if (strcmp(disk->file_table[i].name, filename) == 0) {
            File* file = &disk->file_table[i];
            
            // Free sectors in sector map
            for (int j = 0; j < file->num_sectors; j++) {
                disk->sector_map[file->start_sector + j] = false;
            }

            // Remove file from file table
            memmove(&disk->file_table[i], &disk->file_table[i + 1], (disk->num_files - i - 1) * sizeof(File));
            disk->num_files--;

            return true;
        }
    }
    fprintf(stderr, "File not found\n");
    return false;
}

// List all files on disk
void list_files(Disk* disk) {
    printf("Files on disk:\n");
    for (int i = 0; i < disk->num_files; i++) {
        printf("%s (Size: %d bytes)\n", disk->file_table[i].name, disk->file_table[i].num_sectors * SECTOR_SIZE);
    }
}

int main() {
    Disk* disk = init_disk();
    if (disk == NULL) {
        return 1;
    }

    printf("Disk Storage Simulation\n");
    printf("=======================\n");

    // Write some files
    const char* file1_content = "Hello, this is file 1 content.";
    const char* file2_content = "This is the content of file 2. It's a bit longer than file 1.";

    if (write_file(disk, "file1.txt", (const unsigned char*)file1_content, strlen(file1_content) + 1)) {
        printf("File 'file1.txt' written successfully.\n");
    }

    if (write_file(disk, "file2.txt", (const unsigned char*)file2_content, strlen(file2_content) + 1)) {
        printf("File 'file2.txt' written successfully.\n");
    }

    // List files
    list_files(disk);

    // Read and display file content
    int size;
    unsigned char* content = read_file(disk, "file1.txt", &size);
    if (content != NULL) {
        printf("\nContent of file1.txt: %s\n", content);
        free(content);
    }

    // Delete a file
    if (delete_file(disk, "file2.txt")) {
        printf("\nFile 'file2.txt' deleted successfully.\n");
    }

    // List files again
    list_files(disk);

    // Clean up
    free_disk(disk);

    return 0;
}