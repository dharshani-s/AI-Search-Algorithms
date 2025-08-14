#include <stdio.h>
#include <limits.h>

#define MAX 100

int graph[MAX][MAX], h[MAX];
int n = 7, e = 7, start = 0, goal = 6, beamWidth = 2;

int main() {
    // Initialize adjacency
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = INT_MAX;

    // Edges
    int edges[7][3] = {
        {0, 1, 3}, {0, 2, 5}, {1, 2, 4}, {2, 3, 4},
        {3, 5, 6}, {1, 4, 5}, {4, 6, 3}
    };
    for (int i = 0; i < e; i++) {
        graph[edges[i][0]][edges[i][1]] = edges[i][2];
        graph[edges[i][1]][edges[i][0]] = edges[i][2];
    }

    // Heuristic values
    int heuristics[7] = {999, 7, 6, 7, 3, 4, 0};
    for (int i = 0; i < n; i++) h[i] = heuristics[i];

    int current = start;
    int visited[MAX] = {0};
    visited[current] = 1;

    printf("Path: %d", current);

    while (current != goal) {
        // Collect neighbors
        int candidates[MAX], candSize = 0;
        for (int j = 0; j < n; j++) {
            if (graph[current][j] != INT_MAX && !visited[j]) {
                candidates[candSize++] = j;
            }
        }

        if (candSize == 0) {
            printf("\nNo path found.\n");
            return 0;
        }

        // Sort candidates by heuristic
        for (int i = 0; i < candSize - 1; i++) {
            for (int j = i + 1; j < candSize; j++) {
                if (h[candidates[j]] < h[candidates[i]]) {
                    int tmp = candidates[i];
                    candidates[i] = candidates[j];
                    candidates[j] = tmp;
                }
            }
        }

        // Pick best among top beamWidth
        int nextNode = candidates[0]; // The very best
        visited[nextNode] = 1;
        printf(" -> %d", nextNode);
        current = nextNode;
    }

    printf("\n");
    return 0;
}
