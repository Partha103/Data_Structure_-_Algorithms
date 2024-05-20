#include <stdio.h>
#include <stdlib.h>
#include "../includes/routes.h"

int read_routes(const char* filename, Route** routes, int* num_routes) {
    if (!filename || !routes || !num_routes) {
        fprintf(stderr, "Invalid input parameters\n");
        return -1;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening routes file");
        return -1;
    }

    *num_routes = 0;
    *routes = NULL; // Initialize to NULL to allow realloc to work properly

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        // Reallocate memory for routes array
        Route* tmp = realloc(*routes, (*num_routes + 1) * sizeof(Route));
        if (!tmp) {
            fclose(file);
            free(*routes); 
            *routes = NULL;
            return -1;
        }
        *routes = tmp;

        // Parse line and store data in routes array
        if (sscanf(line, "%d,%d,%d,%f", &((*routes)[*num_routes].id), &((*routes)[*num_routes].from_airport_id), &((*routes)[*num_routes].to_airport_id), &((*routes)[*num_routes].distance)) == 4) {
            (*num_routes)++;
        }
    }

    fclose(file);
    return 0;
}