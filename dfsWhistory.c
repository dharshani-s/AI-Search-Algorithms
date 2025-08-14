#include <stdio.h>

#define MAX 100

int visited[MAX];
int parent[MAX];
int found = 0;
int goalNode;

void reconstructPath(int start, int goal) {
    int path[MAX], len = 0;
    int current = goal;
    
    while (current != -1) {
        path[len++] = current;
        current = parent[current];
    }
    
    printf("Path: ");
    for (int i = len - 1; i >= 0; i--)
        printf("%d ", path[i]);
    printf("\n");
}

void DFS(int graph[MAX][MAX], int n, int node) {
    if (found) return; // already found, stop
    visited[node] = 1;
    
    if (node == goalNode) {
        found = 1;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (graph[node][i] && !visited[i]) {
            parent[i] = node;
            DFS(graph, n, i);
            if (found) return;
        }
    }
}

int main() {
    int n, edges, u, v;
    int graph[MAX][MAX] = {0};

    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; // undirected
    }

    int start;
    printf("Enter start and goal: ");
    scanf("%d %d", &start, &goalNode);

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    DFS(graph, n, start);

    if (found)
        reconstructPath(start, goalNode);
    else
        printf("No path found\n");

    return 0;
}
