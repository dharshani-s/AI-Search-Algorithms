#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int h[MAX];

int main() {
    int n, e;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize adjacency matrix with large values (no edge)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = INT_MAX;

    printf("Enter edges (u v cost):\n");
    for (int i = 0; i < e; i++) {
        int u, v, cost;
        scanf("%d %d %d", &u, &v, &cost);
        graph[u][v] = cost;
        graph[v][u] = cost; // undirected graph
    }

    int start, goal;
    printf("Enter start node: ");
    scanf("%d", &start);
    printf("Enter goal node: ");
    scanf("%d", &goal);

    printf("Enter heuristic values for each node:\n");
    for (int i = 0; i < n; i++) {
        printf("h[%d]: ", i);
        scanf("%d", &h[i]);
    }

    // Hill climbing with history
    int current = start;
    visited[current] = 1;

    printf("Path: %d", current);

    while (current != goal) {
        int best_neighbor = -1;
        int best_h = INT_MAX;

        // First try to find better neighbor (lower h)
        for (int i = 0; i < n; i++) {
            if (graph[current][i] != INT_MAX && !visited[i]) {
                if (h[i] < best_h) {
                    best_h = h[i];
                    best_neighbor = i;
                }
            }
        }

        // If no unvisited neighbor, stop
        if (best_neighbor == -1) {
            printf("\nNo more unvisited neighbors. Search stopped.\n");
            break;
        }

        current = best_neighbor;
        visited[current] = 1;
        printf(" -> %d", current);
    }

    if (current == goal) {
        printf("\nGoal reached!\n");
    }

    return 0;
}
