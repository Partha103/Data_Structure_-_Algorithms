#include <stdio.h>
#include <stdlib.h>
#include "../includes/airports.h"
#include "../includes/routes.h"
#include "../includes/rtree.h"

int main() {
    Airport* airports = NULL;
    Route* routes = NULL;
    int num_airports = 0, num_routes = 0;

    // Read airports
    if (read_airports("data/airports.csv", &airports, &num_airports) != 0) {
        fprintf(stderr, "Failed to read airports.\n");
        goto cleanup;
        return -1;
    }

    // Read routes
    if (read_routes("data/routes.csv", &routes, &num_routes) != 0) {
        fprintf(stderr, "Failed to read routes.\n");
        goto cleanup;
        return -1;
    }

    // Create R-tree
    RTree* rtree = RTreeCreate();
    if (!rtree) {
        fprintf(stderr, "Failed to create R-tree.\n");
        goto cleanup;
    }

    // Optimize air traffic
    optimize_air_traffic(airports, num_airports, routes, num_routes);


    printf("Air traffic optimization successful.\n");

cleanup:
    // Clean up resources
    RTreeDestroy(rtree);
    free(airports);
    free(routes);

    return 0;
}
