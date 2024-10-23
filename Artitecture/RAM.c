#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define RAM_SIZE 1024  // Size of RAM in bytes
#define WORD_SIZE 4    // Size of a word in bytes

// Structure to represent our RAM
typedef struct {
    uint8_t* memory;   // Pointer to the memory array
    size_t size;       // Size of the memory in bytes
} RAM;

// Function to initialize RAM
RAM* init_ram(size_t size) {
    RAM* ram = (RAM*)malloc(sizeof(RAM));
    if (ram == NULL) {
        fprintf(stderr, "Failed to allocate RAM structure\n");
        return NULL;
    }
    
    ram->memory = (uint8_t*)calloc(size, sizeof(uint8_t));
    if (ram->memory == NULL) {
        fprintf(stderr, "Failed to allocate memory for RAM\n");
        free(ram);
        return NULL;
    }
    
    ram->size = size;
    return ram;
}

// Function to write a word to RAM
void write_word(RAM* ram, size_t address, uint32_t value) {
    if (address + WORD_SIZE > ram->size) {
        fprintf(stderr, "Memory access out of bounds\n");
        return;
    }
    
    // Write the word byte by byte (little-endian)
    for (int i = 0; i < WORD_SIZE; i++) {
        ram->memory[address + i] = (value >> (8 * i)) & 0xFF;
    }
}

// Function to read a word from RAM
uint32_t read_word(RAM* ram, size_t address) {
    if (address + WORD_SIZE > ram->size) {
        fprintf(stderr, "Memory access out of bounds\n");
        return 0;
    }
    
    // Read the word byte by byte (little-endian)
    uint32_t value = 0;
    for (int i = 0; i < WORD_SIZE; i++) {
        value |= (uint32_t)(ram->memory[address + i]) << (8 * i);
    }
    
    return value;
}

// Function to free RAM
void free_ram(RAM* ram) {
    if (ram != NULL) {
        free(ram->memory);
        free(ram);
    }
}

// Function to display RAM contents
void display_ram(RAM* ram, size_t start, size_t end) {
    printf("RAM contents from address %zu to %zu:\n", start, end);
    for (size_t i = start; i < end; i += WORD_SIZE) {
        printf("Address %zu: 0x%08X\n", i, read_word(ram, i));
    }
    printf("\n");
}

int main() {
    // Initialize RAM
    RAM* ram = init_ram(RAM_SIZE);
    if (ram == NULL) {
        return 1;
    }
    
    printf("RAM Simulation\n");
    printf("==============\n");
    printf("Total RAM size: %zu bytes\n", ram->size);
    printf("Word size: %d bytes\n\n", WORD_SIZE);

    // Write some values to RAM
    write_word(ram, 0, 0x12345678);
    write_word(ram, 4, 0xABCDEF01);
    write_word(ram, 8, 0x98765432);

    // Display RAM contents
    display_ram(ram, 0, 16);

    // Read and display a specific address
    size_t read_address = 4;
    printf("Value at address %zu: 0x%08X\n\n", read_address, read_word(ram, read_address));

    // Modify a value in RAM
    write_word(ram, 8, 0x11223344);
    printf("After modifying address 8:\n");
    display_ram(ram, 0, 16);

    // Try to access out of bounds (should print an error message)
    printf("Attempting to access out of bounds:\n");
    write_word(ram, RAM_SIZE, 0xFFFFFFFF);
    read_word(ram, RAM_SIZE);

    // Free RAM
    free_ram(ram);

    return 0;
}