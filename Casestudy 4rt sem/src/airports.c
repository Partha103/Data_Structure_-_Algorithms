#include <stdio.h>
#include <stdlib.h>
#include "../includes/airports.h"

#define MAX_LINE_LENGTH 1024

int read_airports(const char* filename, Airport** airports, int* num_airports) {
    if (!filename || !airports || !num_airports) {
        fprintf(stderr, "Invalid input parameters\n");
        return -1;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening airports file");
        return -1;
    }

    *num_airports = 0;
    *airports = NULL; // Initialize to NULL to allow realloc to work properly

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        // Reallocate memory for airports array
        Airport* tmp = realloc(*airports, (*num_airports + 1) * sizeof(Airport));
        if (!tmp) {
            fclose(file);
            free(*airports); // Free previously allocated memory
            *airports = NULL;
            return -1;
        }
        *airports = tmp;

        // Parse line and store data in airports array
        if (sscanf(line, "%d,%f,%f", &((*airports)[*num_airports].id), &((*airports)[*num_airports].latitude), &((*airports)[*num_airports].longitude)) == 3) {
            (*num_airports)++;
        }
    }

    fclose(file);
    return 0;
}
