#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define WIDTH 1920
#define HEIGHT 1080
#define NUM_THREADS 8
#define Red r
#define Green g
#define Blue b

typedef struct {
    unsigned char r, g, b;
} Pixel;

typedef struct {
    int start_y;
    int end_y;
    Pixel (*image)[WIDTH];
} ThreadArgs;

// Simulated shader function
void pixel_shader(int x, int y, Pixel *pixel) {
    // Simple gradient effect
    pixel->r = (unsigned char)((float)x / WIDTH * 255);
    pixel->g = (unsigned char)((float)y / HEIGHT * 255);
    pixel->b = (unsigned char)(((float)x / WIDTH + (float)y / HEIGHT) / 2 * 255);
}

// Thread function for parallel processing
void* process_chunk(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    for (int y = args->start_y; y < args->end_y; y++) {
        for (int x = 0; x < WIDTH; x++) {
            pixel_shader(x, y, &args->image[y][x]);
        }
    }
    return NULL;
}

int main() {
    // Allocate memory for the image
    Pixel (*image)[WIDTH] = malloc(HEIGHT * sizeof(*image));
    if (image == NULL) {
        fprintf(stderr, "Failed to allocate memory for the image\n");
        return 1;
    }

    // Set up threads
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];
    int chunk_size = HEIGHT / NUM_THREADS;

    printf("Simple GPU Simulation\n");
    printf("=====================\n");
    printf("Image resolution: %dx%d\n", WIDTH, HEIGHT);
    printf("Number of threads: %d\n", NUM_THREADS);

    // Record start time
    clock_t start = clock();

    // Create and run threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].start_y = i * chunk_size;
        thread_args[i].end_y = (i == NUM_THREADS - 1) ? HEIGHT : (i + 1) * chunk_size;
        thread_args[i].image = image;
        pthread_create(&threads[i], NULL, process_chunk, &thread_args[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Record end time
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Rendering completed in %f seconds\n", cpu_time_used);

    // Save the image as a PPM file
    FILE *fp = fopen("output.ppm", "wb");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file for writing\n");
        free(image);
        return 1;
    }

    fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            fwrite(&image[y][x], 1, sizeof(Pixel), fp);
        }
    }
    fclose(fp);

    printf("Image saved as 'output.ppm'\n");

    // Clean up
    free(image);

    return 0;
}