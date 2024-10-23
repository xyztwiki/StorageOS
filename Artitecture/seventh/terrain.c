#include "math.h"
#define Height 1
#define Width 1
#define MAX_Height 256
// Function to initialize the terrain with random values
void initializeTerrain(int terrain[Height][Width]) {
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            terrain[y][x] = rand() % (MAX_Height + 1);
        }
    }
}
// Function to apply algebraic operations to smooth and vary the terrain
void generateTerrain(int terrain[Height][Width]) {
    for (int y = 1; y < Height - 1; y++) {
        for (int x = 1; x < Width - 1; x++) {
            // Apply a simple averaging with neighboring cells
            terrain[y][x] = (terrain[y][x] + terrain[y-1][x] + 
                             terrain[y+1][x] + terrain[y][x-1] + terrain[y][x+1]) / 5;
            
            // Add some random variation
            terrain[y][x] += (rand() % 3) - 1;
            
            // Ensure the Height stays within bounds
            if (terrain[y][x] < 0) terrain[y][x] = 0;
            if (terrain[y][x] > MAX_Height) terrain[y][x] = MAX_Height;
        }
    }
}
// Function to display the terrain
void displayTerrain(int terrain[Height][Width]) {
    const char* symbols = " .:-=+*#%@"; // Different symbols for Height levels
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            printf("%c", symbols[terrain[y][x]]);
        }
        printf("\n");
    }
}