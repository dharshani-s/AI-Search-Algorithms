#include <stdio.h>
#include <limits.h>

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
int oracleLengths[100]; // store path lengths
int oraclePaths[100][NODES]; // store actual paths
int pathSizes[100]; // store sizes of each path

// Adjacency matrix
int graph[NODES][NODES];

void dfs(int node, int currentCost) {
    visited[node] = 1;
    path[pathIndex++] = node;

    if (node == goal) {
        // Store oracle
        for (int i = 0; i < pathIndex; i++) {
            oraclePaths[totalOracles][i] = path[i];
        }
        pathSizes[totalOracles] = pathIndex;
        oracleLengths[totalOracles] = currentCost;
        totalOracles++;
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

    // Step 1: Find all oracles
    dfs(0, 0);

    // Step 2: Ask for path lengths (simulate input from user)
    printf("Enter lengths for the %d oracle paths:\n", totalOracles);
    for (int i = 0; i < totalOracles; i++) {
        printf("Oracle %d path length: ", i + 1);
        scanf("%d", &oracleLengths[i]);
    }

    // Step 3: Branch and Bound to pick shortest
    int minLen = INT_MAX;
    int bestOracle = -1;

    for (int i = 0; i < totalOracles; i++) {
        if (oracleLengths[i] < minLen) {
            minLen = oracleLengths[i];
            bestOracle = i;
        }
    }

    // Step 4: Output best oracle
    printf("\nBest Oracle (Shortest Path) found using Branch and Bound:\n");
    printf("Path: ");
    for (int j = 0; j < pathSizes[bestOracle]; j++) {
        printf("%d", oraclePaths[bestOracle][j]);
        if (j != pathSizes[bestOracle] - 1) printf(" -> ");
    }
    printf("\nPath Length: %d\n", minLen);

    return 0;
}
