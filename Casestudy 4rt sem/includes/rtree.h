#ifndef RTREE_H
#define RTREE_H

#include "common.h"
#include <float.h> 
#include <stdio.h> 
#include <stdlib.h>

// Define constants
#define MAX_RECTS_PER_NODE 4

// Define structures
typedef struct RTreeNode RTreeNode;

struct RTree
{
    RTreeNode* root;
};

typedef struct RTree RTree;

// Define function prototypes
RTree* RTreeCreate();
void RTreeDestroy(RTree* tree);
void RTreeInsertRect(const RTreeRect* rect, int id, RTree* tree);
RTreeList* RTreeSearch(const RTreeRect* rect, const RTree* tree);
void RTreeFreeList(RTreeList* list);
void optimize_air_traffic( Airport* airports, int num_airports, Route* routes, int num_routes);

#endif /* RTREE_H */