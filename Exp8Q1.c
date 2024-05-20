#include <stdio.h>
#include <limits.h>

#define V 70        
#define INF INT_MAX 

void writeDistanceMatrixToFile(int dist[][V], int n, char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file %s.\n", filename);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
                fprintf(file, "INF ");
            else
                fprintf(file, "%d ", dist[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int minDistance(int dist[], int visited[], int n)
{
    int min = INF, min_index;
    for (int v = 0; v < n; v++)
    {
        if (visited[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printSolution(int dist[], int n, int parent[], int src, char *filename)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error opening file %s.\n", filename);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (i != src)
        {
            fprintf(file, "Path from %d to %d: ", src, i);
            int j = i;
            while (parent[j] != -1)
            {
                fprintf(file, "%d <- ", j);
                j = parent[j];
            }
            fprintf(file, "%d\n", src);
        }
    }

    fclose(file);
}

void dijkstra(int graph[V][V], int src)
{
    int dist[V];    
    int visited[V]; 
    int parent[V];  

    for (int i = 0; i < V; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited, V);

        visited[u] = 1;

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    writeDistanceMatrixToFile(graph, V, "output1.txt");

    printSolution(dist, V, parent, src, "output.txt");
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file distance_matrix_input.txt.\n");
        return 1;
    }

    int graph[V][V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);

    for (int i = 0; i < V; i++)
    {
        dijkstra(graph, i);
    }

    return 0;
}