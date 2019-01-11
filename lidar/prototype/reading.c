/**
 * @brief A simple program to read the point cloud data from Apollo
 * @author Krerkkiat Chusap
 *
 * For full visualization please see the Jupyter nobook file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NUMBER_OF_FILE 2

typedef struct __attribute__((__packed__)) _Point {
//typedef struct _Data {
  float x;
  float y;
  float z;
  float i;
} Point;

/**
 * @brief Return file size in byte.
 */
long int get_file_size(FILE *file) {
  long int file_size;

  // Seek to the end.
  fseek(file, 0L, SEEK_END);

  // Get the current offset.
  file_size = ftell(file);

  // Reset file's position back to the begining.
  fseek(file, 0L, SEEK_SET);

  return file_size;
}

int main(int argc, char *argv[]) {
  // An array of frame (an array of array of Point).
  size_t i;
  Point *frames[100];
  long int file_size;

  char file_name[500];

  for (i = 0; i < NUMBER_OF_FILE; i++) {
    // Open a file.
    sprintf(file_name, "./3d-sample/bin_files/002_%08d.bin", (int) i);
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
      fprintf(stderr, "Error occurs while open a file.\n");
      exit(EXIT_FAILURE);
    }

    // Get the file size.
    file_size = get_file_size(file);

    printf("will be reading from a file of size: %ld bytes from %s\n", file_size, file_name);
    
    // Allocate the memory.
    void *ret = malloc(file_size);
    if (ret == NULL) {
      fprintf(stderr, "Error occur while allocating memory for points for a frame.\n");
      exit(EXIT_FAILURE);
    }
    frames[i] = (Point *) ret;

    // Read all the point from the file.
    if (file_size % sizeof(Point) != 0) {
      fprintf(stderr, "Size of a file does not align properly with Point structure.\n");
      exit(EXIT_FAILURE);
    }
    fread(frames[i], sizeof(Point), file_size / sizeof(Point), file);

    // Close the file.
    fclose(file);
  }

  // Using the data.
  // Technically, we can fork the process here to start the viewer server,
  // but the socket connection may be too much work.

  for (int f = 0; f < NUMBER_OF_FILE; f++) {
    // Display the first 10 data points.
    for (int p = 0; p < 10; p++) {
      printf("%.3f %.3f %.3f %.3f\n", frames[f][p].x, frames[f][p].y, frames[f][p].z, frames[f][p].i);
    }
    printf("\n");
  }

  // Cleaning.
  for (i = 0; i < NUMBER_OF_FILE; i++) {
    free(frames[i]);
  }

  return 0;
}
