#include <stdio.h>
#include <limits.h>

#define N 7
#define E 7

// Graph edges: u, v, cost
int edges[E][3] = {
    {0, 1, 3},
    {0, 2, 5},
    {1, 2, 4},
    {2, 3, 4},
    {3, 5, 6},
    {1, 4, 5},
    {4, 6, 3}
};

// Heuristic values (h[0] = 999 as start node is not goal)
int heuristic[N] = {999, 7, 6, 7, 3, 4, 0};

// Adjacency matrix
int graph[N][N];

int visited[N];
int bestCost = INT_MAX;
int bestPath[N];
int bestPathLen = 0;

void dfs(int node, int goal, int path[], int pathLen, int cost, int oracleCost) {
    if (cost > oracleCost) return; // pruning based on oracle

    if (cost + heuristic[node] >= bestCost) return; // bounding with heuristic

    if (node == goal) {
        if (cost < bestCost) {
            bestCost = cost;
            bestPathLen = pathLen;
            for (int i = 0; i < pathLen; i++)
                bestPath[i] = path[i];
        }
        return;
    }

    visited[node] = 1;

    for (int i = 0; i < N; i++) {
        if (graph[node][i] != 0 && !visited[i]) {
            path[pathLen] = i;
            dfs(i, goal, path, pathLen + 1, cost + graph[node][i], oracleCost);
        }
    }

    visited[node] = 0;
}

int main() {
    // Initialize adjacency matrix
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            graph[i][j] = 0;

    for (int i = 0; i < E; i++)
        graph[edges[i][0]][edges[i][1]] = graph[edges[i][1]][edges[i][0]] = edges[i][2];

    int oracleCost;
    printf("Enter known oracle path cost: ");
    scanf("%d", &oracleCost);

    int start = 0, goal = 6;
    int path[N];
    path[0] = start;

    dfs(start, goal, path, 1, 0, oracleCost);

    printf("\nBest Path Found: ");
    for (int i = 0; i < bestPathLen; i++) {
        printf("%d", bestPath[i]);
        if (i < bestPathLen - 1) printf(" -> ");
    }
    printf("\nPath Cost: %d\n", bestCost);

    return 0;
}
