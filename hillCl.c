#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int main() {
    int n = 7;  // number of nodes
    int e = 7;  // number of edges
    int start = 0;
    int goal = 6;

    int graph[MAX][MAX] = {0};

    // Edges (u, v, cost)
    int edges[7][3] = {
        {0, 1, 3},
        {0, 2, 5},
        {1, 2, 4},
        {2, 3, 4},
        {3, 5, 6},
        {1, 4, 5},
        {4, 6, 3}
    };

    for (int i = 0; i < e; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[u][v] = 1;
        graph[v][u] = 1; // undirected
    }

    // Heuristic values
    int h[MAX] = {999, 7, 6, 7, 3, 4, 0};

    int visited[MAX] = {0};
    int path[MAX], pathLen = 0;

    int current = start;
    path[pathLen++] = current;
    visited[current] = 1;

    while (current != goal) {
        int nextNode = -1;
        int minH = 9999;

        // Look at all neighbors
        for (int i = 0; i < n; i++) {
            if (graph[current][i] && !visited[i]) {
                if (h[i] < minH) {
                    minH = h[i];
                    nextNode = i;
                }
            }
        }

        if (nextNode == -1) {
            printf("No path found.\n");
            return 0;
        }

        current = nextNode;
        visited[current] = 1;
        path[pathLen++] = current;
    }

    // Print path
    printf("Path: ");
    for (int i = 0; i < pathLen; i++) {
        printf("%d", path[i]);
        if (i != pathLen - 1) printf(" -> ");
    }
    printf("\n");

    return 0;
}
