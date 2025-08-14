#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int graph[MAX][MAX]; // adjacency matrix
bool visited[MAX];
int parent[MAX]; // to reconstruct path
bool found = false;

void printPath(int start, int goal) {
    if (goal == start) {
        printf("%d ", start);
        return;
    }
    printPath(start, parent[goal]);
    printf("%d ", goal);
}

void DFS(int current, int goal, int nodes) {
    visited[current] = true;

    if (current == goal) {
        //printf("Goal %d found! Path: ", goal);
        printPath(parent[0], goal); // assumes DFS started from parent[0] == start
        printf("\n");
        found = true;
        return;
    }

    for (int i = 0; i < nodes && !found; i++) {
        if (graph[current][i] && !visited[i]) {
            parent[i] = current;
            DFS(i, goal, nodes);
        }
    }
}

int main() {
    int nodes, edges, src, dest, start, goal;

    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    // Initialize adjacency matrix
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            graph[i][j] = 0;
        }
        visited[i] = false;
        parent[i] = -1;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter each edge (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &src, &dest);
        graph[src][dest] = 1;
        graph[dest][src] = 1; // undirected
    }

    printf("Enter start node: ");
    scanf("%d", &start);
    printf("Enter goal node: ");
    scanf("%d", &goal);

    parent[start] = start; // for path reconstruction
    DFS(start, goal, nodes);

    if (!found) {
        printf("Goal not found in the graph.\n");
    }

    return 0;
}

// 0 1
// 0 2
// 1 2
// 2 3
// 3 5
// 1 4
// 4 6