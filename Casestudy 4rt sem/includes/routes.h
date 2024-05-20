#ifndef ROUTES_H
#define ROUTES_H

#include "common.h"

int read_routes(const char* filename, Route** routes, int* num_routes);
// In routes.h
void optimize_air_traffic( Airport* airports, int num_airports, Route* routes, int num_routes);

#endif /* ROUTES_H */