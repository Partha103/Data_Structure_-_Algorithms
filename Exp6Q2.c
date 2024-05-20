#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAX_VERTICES 24
#define MAX_EDGES 76

void floydWarshall(float graphMatrix[][MAX_VERTICES]);
void initializeGraphMatrix(float graphMatrix[][MAX_VERTICES]);
void readGraphFromCSV(const char *filename, float graphMatrix[][MAX_VERTICES]);
void printGraphMatrix(float graphMatrix[][MAX_VERTICES]);
void printGraphMatrixInCSV(const char *filename, float graphMatrix[][MAX_VERTICES]);

int main()
{

    float graphMatrix[MAX_VERTICES][MAX_VERTICES];

    initializeGraphMatrix(graphMatrix);

    readGraphFromCSV("SiouxFallsNetwork.csv", graphMatrix);

    printGraphMatrix(graphMatrix);

    floydWarshall(graphMatrix);

    return 0;
}

void floydWarshall(float graphMatrix[][MAX_VERTICES])
{
    int i, j, k;

    for (k = 0; k < MAX_VERTICES; k++)
    {
        for (i = 0; i < MAX_VERTICES; i++)
        {
            for (j = 0; j < MAX_VERTICES; j++)
            {
                if (graphMatrix[i][j] > (graphMatrix[i][k] + graphMatrix[k][j]) && (graphMatrix[k][j] != FLT_MAX && graphMatrix[i][k] != FLT_MAX)){
                    graphMatrix[i][j] = graphMatrix[i][k] + graphMatrix[k][j];
                }
            }
        }
    }

    printGraphMatrix(graphMatrix);
    printGraphMatrixInCSV("Output2.csv", graphMatrix);
}

void initializeGraphMatrix(float graphMatrix[][MAX_VERTICES])
{
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        for (int j = 0; j < MAX_VERTICES; j++)
        {
            graphMatrix[i][j] = i == j ? 0 : FLT_MAX;
        }
    }
}

void readGraphFromCSV(const char *filename, float graphMatrix[][MAX_VERTICES])
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[100]; 
    fgets(line, sizeof(line), file);

    int link;
    int src, dest;
    float weight;
    for (int i = 0; i < MAX_EDGES; ++i)
    {
        fscanf(file, "%d,%d,%d,%f\n", &link, &src, &dest, &weight);
        if (src - 1 < 0 || src - 1 >= MAX_VERTICES || dest - 1 < 0 || dest - 1 >= MAX_VERTICES)
        {
            printf("Error: Indices out of bounds\n");
            continue;
        }

        graphMatrix[src - 1][dest - 1] = weight;
    }

    fclose(file);
}

void printGraphMatrix(float graphMatrix[][MAX_VERTICES])
{
    printf("Graph Matrix:\n");
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        for (int j = 0; j < MAX_VERTICES; j++)
        {
            if (graphMatrix[i][j] == FLT_MAX)
            {
                printf("INF\t");
            }
            else
            {
                printf("%.2f\t", graphMatrix[i][j]);
            }
        }
        printf("\n");
    }
}

void printGraphMatrixInCSV(const char *filename, float graphMatrix[][MAX_VERTICES])
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Nodes,");
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        fprintf(file, "Node %d,", i + 1);
    }
    fprintf(file, "\n");

    for (int i = 0; i < MAX_VERTICES; i++)
    {
        fprintf(file, "Node %d,", i + 1);
        for (int j = 0; j < MAX_VERTICES; j++)
        {
            fprintf(file, "%.2f,", graphMatrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}