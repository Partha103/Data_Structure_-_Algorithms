#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100
#define INF INT_MAX

int minKey(int key[], int mstSet[], int numNodes)
{
    int min = INF, min_index;
    for (int v = 0; v < numNodes; v++)
    {
        if (mstSet[v] == 0 && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[MAX_NODES][MAX_NODES], int numNodes, FILE *outputFile)
{
    for (int i = 1; i < numNodes; i++)
        fprintf(outputFile, "%d - %d\n", parent[i], i);
}

void primMST(int graph[MAX_NODES][MAX_NODES], int numNodes, FILE *outputFile)
{
    int parent[MAX_NODES]; 
    int key[MAX_NODES];    
    int mstSet[MAX_NODES];

    for (int i = 0; i < numNodes; i++)
    {
        key[i] = INF;
        mstSet[i] = 0;
    }

    key[0] = 0;     
    parent[0] = -1; 

    for (int count = 0; count < numNodes - 1; count++)
    {
        int u = minKey(key, mstSet, numNodes);

        mstSet[u] = 1;

        for (int v = 0; v < numNodes; v++)
        {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, numNodes, outputFile);
}

int main()
{
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening files.");
        return 1;
    }

    int numNodes = MAX_NODES;
    int graph[MAX_NODES][MAX_NODES];
    for (int i = 0; i < numNodes; i++)
    {
        for (int j = 0; j < numNodes; j++)
        {
            fscanf(inputFile, "%d", &graph[i][j]);
        }
    }

    primMST(graph, numNodes, outputFile);

    printf("Minimum Spanning Tree generated and written to output.txt.\n");

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}