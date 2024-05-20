#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <limits.h>

#define MAX_NODES 15
#define INF INT_MAX

int graph[MAX_NODES][MAX_NODES]; // adjacency matrix representation of the graph
int num_nodes; // number of nodes in the graph

// Function to compute all-pairs shortest paths using Floyd-Warshall algorithm
void floyd_warshall() {
    int i, j, k;

    for (k = 0; k < num_nodes; k++) {
        for (i = 0; i < num_nodes; i++) {
            for (j = 0; j < num_nodes; j++) {
                if (graph[i][k] != INF && graph[k][j] != INF && graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

// Function to read the graph from a CSV file
void read_graph(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    int source, destination, weight;
    while (fscanf(file, "%d,%d,%d\n", &source, &destination, &weight) != EOF) {
        graph[source][destination] = 1; 
    }

    fclose(file);
}

// Function to read demand table and compute demand along a given path
int compute_demand(int path[], int path_length, int demand[MAX_NODES][MAX_NODES]) {
    int total_demand = 0;
    for (int i = 0; i < path_length - 1; i++) {
        total_demand += demand[path[i]][path[i + 1]];
    }
    return total_demand;
}

// Recursive function to find subsets with the target sum
void findSubsets(int demand[], int n, int targetSum, int index, int currSum, int subset[], int subsetSize, bool *subsetFound, int *subsetCount, int maxSubsets) {
    if (*subsetCount >= maxSubsets || *subsetFound) {
        // Stop recursion if all subsets have been found or if a subset has been found
        return;
    }
    if (currSum == targetSum) {
        // Print the subset
        printf("Subset is: { ");
        for (int i = 0; i < subsetSize; i++) {
            printf("%d ", subset[i]);
        }
        printf("}\n");
        *subsetFound = true; // Set the flag to true
        (*subsetCount)++; // Increment the subset count
        return;
    }
    if (index >= n || currSum > targetSum) {
        return;
    }

    // Include the current element in the subset
    subset[subsetSize] = demand[index];
    findSubsets(demand, n, targetSum, index + 1, currSum + demand[index], subset, subsetSize + 1, subsetFound, subsetCount, maxSubsets);

    // Skip duplicates
    while (index < n - 1 && demand[index] == demand[index + 1]) {
        index++;
    }

    // Exclude the current element from the subset
    findSubsets(demand, n, targetSum, index + 1, currSum, subset, subsetSize, subsetFound, subsetCount, maxSubsets);
}

// Function to update the graph based on selected demands
void update_graph(int subset[], int subset_size, int demand[MAX_NODES][MAX_NODES]) {
    // Reset the graph
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            graph[i][j] = (i == j) ? 0 : INF;
        }
    }

    // Update the graph based on selected demands
    for (int i = 0; i < subset_size; i++) {
        int demand_index = subset[i];
        for (int j = 0; j < num_nodes; j++) {
            for (int k = 0; k < num_nodes; k++) {
                if (demand[j][k] != INF) {
                    graph[j][k] = 1; // Assuming unweighted edges
                }
            }
        }
    }
}

int main() {
    read_graph("figure2.csv");
    num_nodes = MAX_NODES; // Assuming the maximum number of nodes

    floyd_warshall();

    // Read demand table
    int demand[MAX_NODES][MAX_NODES];
    FILE *demand_file = fopen("table_7.csv", "r");
    if (demand_file == NULL) {
        printf("Error opening file table_7.csv\n");
        exit(1);
    }

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            fscanf(demand_file, "%d,", &demand[i][j]);
        }
    }

    fclose(demand_file);

    // Collect demands from shortest paths with total demand <= 500
    int demands[MAX_NODES * MAX_NODES]; // Assuming total demands won't exceed this limit
    int demand_count = 0;
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (i != j && graph[i][j] != INF) {
                // Compute demand along shortest path from i to j
                int path[] = {i, j};
                int total_path_demand = compute_demand(path, 2, demand);
                if (total_path_demand <= 500) {
                    demands[demand_count++] = total_path_demand;
                }
            }
        }
    }

    // Find subsets with the target sum using recursive function
    int targetSum = 500;
    int subset[MAX_NODES];
    int subsetCount = 0;
    int maxSubsets = 10;

    bool subsetFound = false; // Initialize the flag
    findSubsets(demands, demand_count, targetSum, 0, 0, subset, 0, &subsetFound, &subsetCount, maxSubsets);

    if (!subsetFound) {
        printf("No subset found with the target sum.\n");
    }

    return 0;
}