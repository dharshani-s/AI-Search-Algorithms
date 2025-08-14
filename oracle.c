#include <stdio.h>

#define NODES 7
#define EDGES 7

// Hardcoded edges: {u, v, cost}
int edges[EDGES][3] = {
    {0, 1, 3},
    {0, 2, 5},
    {1, 2, 4},
    {2, 3, 4},
    {3, 5, 6},
    {1, 4, 5},
    {4, 6, 3}
};

int goal = 6;
int visited[NODES];
int path[NODES];
int pathIndex = 0;
int totalOracles = 0;

// Adjacency matrix
int graph[NODES][NODES];

void dfs(int node, int currentCost) {
    visited[node] = 1;
    path[pathIndex++] = node;

    if (node == goal) {
        totalOracles++;
        printf("Oracle %d: ", totalOracles);
        for (int i = 0; i < pathIndex; i++) {
            printf("%d", path[i]);
            if (i != pathIndex - 1) printf(" -> ");
        }
        printf(" | Path Length: %d\n", currentCost);
    } else {
        for (int i = 0; i < NODES; i++) {
            if (graph[node][i] != 0 && !visited[i]) {
                dfs(i, currentCost + graph[node][i]);
            }
        }
    }

    pathIndex--;
    visited[node] = 0;
}

int main() {
    // Initialize adjacency matrix
    for (int i = 0; i < NODES; i++) {
        for (int j = 0; j < NODES; j++) {
            graph[i][j] = 0;
        }
    }

    // Fill adjacency matrix
    for (int i = 0; i < EDGES; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int cost = edges[i][2];
        graph[u][v] = cost;
        graph[v][u] = cost; // Undirected graph
    }

    printf("Oracle Search Paths from 0 to %d:\n", goal);
    dfs(0, 0);

    printf("\nTotal Oracles Found: %d\n", totalOracles);
    return 0;
}
