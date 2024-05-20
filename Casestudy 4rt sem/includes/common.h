#ifndef COMMON_H
#define COMMON_H

#define MAX_LINE_LENGTH 1024

typedef struct {
    float min[2];
    float max[2];
    int id;
} RTreeRect;

typedef struct RTreeList {
    int id;
    struct RTreeList* next;
} RTreeList;

typedef struct {
    int id;
    float latitude;
    float longitude;
} Airport;

typedef struct {
    float latitude;
    float longitude;
} Coordinate;

typedef struct {
    int id;
    int from_airport_id;
    int to_airport_id;
    float distance;
    float latitude;
    float longitude;
    Coordinate source;
    Coordinate destination;
    Airport sourceAirport; // Changed from "source" to "sourceAirport"
    Airport destinationAirport; // Changed from "destination" to "destinationAirport"
} Route;

typedef struct RTree RTree; // Forward declaration of RTree structure

#endif /* COMMON_H */
