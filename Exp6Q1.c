#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

struct Edge
{
    int src, dest;
    float weight;
};

struct Graph
{
    int V, E;

    struct Edge *edge;
};

struct Graph *createGraph(int V, int E)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge *)malloc(sizeof(struct Edge) * E);
    return graph;
}

// Utility function to print the shortest paths in the output file
void printPath(FILE *file, int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j] == -1)
        return;

    printPath(file, parent, parent[j]);

    fprintf(file, "-> %d ", j);
}

void printPathToFile(int parent[], int src, int n)
{
    FILE *file = fopen("PathOutput1.csv", "w");
    if (!file)
    {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Source,Destination,Path\n");
    for (int i = 0; i < n; ++i)
    {
        fprintf(file, "%d,%d,%d ", src, i, src);
        printPath(file, parent, i);
        fprintf(file, "\n");
    }

    fclose(file);
}

void printArr(float dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %.2lf\n", i, dist[i]);
}

void printArrinFile(float dist[], int n)
{
    FILE *file = fopen("Output1.csv", "w");
    if (!file)
    {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Vertex,Distance from Source\n");
    for (int i = 0; i < n; ++i)
        fprintf(file, "%d,%.2lf\n", i, dist[i]);
}

void BellmanFord(struct Graph *graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    float dist[V];
    int parent[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = FLT_MAX;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            float weight = graph->edge[j].weight;
            if (dist[u] != FLT_MAX && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }

    for (int i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        float weight = graph->edge[i].weight;
        if (dist[u] != FLT_MAX && dist[u] + weight < dist[v])
        {
            printf("Graph contains negative weight cycle");
            return;
        }
    }

    printArr(dist, V);
    printArrinFile(dist, V);
    printPathToFile(parent, src, V);

    return;
}

void readGraphFromCSV(const char *filename, struct Graph *graph)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Assuming the first line in the CSV file is a header and ignoring it
    char line[100]; // Adjust the size according to your maximum line length
    fgets(line, sizeof(line), file);

    for (int i = 0; i < graph->E; ++i)
    {
        int link;
        fscanf(file, "%d,%d,%d,%f\n", &link, &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    fclose(file);
}

int main()
{
    int V = 24;
    int E = 76;
    struct Graph *graph = createGraph(V, E);

    readGraphFromCSV("SiouxFallsNetwork.csv", graph);

    printf("%d\n", graph->V);
    for (int i = 0; i < graph->E; ++i)
    {
        printf("Edge %d: src=%d, dest=%d, weight=%.f\n", i + 1, graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
    }

    BellmanFord(graph, 0);

    free(graph->edge);
    free(graph);

    return 0;
}