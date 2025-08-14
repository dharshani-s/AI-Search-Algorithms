#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int graph[MAX][MAX]; // adjacency matrix
bool visited[MAX];   // visited nodes for current path
int path[MAX];       // store current path
int pathIndex = 0;
int nodes;           // number of nodes

void britishMuseumSearch(int current, int target) {
    visited[current] = true;
    path[pathIndex++] = current;

    if (current == target) {
        // Found a path — print it
        printf("Path found: ");
        for (int i = 0; i < pathIndex; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        // Try every possible neighbor
        for (int i = 0; i < nodes; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                britishMuseumSearch(i, target);
            }
        }
    }

    // Backtrack — unvisit the node for other paths
    visited[current] = false;
    pathIndex--;
}

int main() {
    int edges, src, dest, start, target;

    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    // Initialize graph
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            graph[i][j] = 0;
        }
        visited[i] = false;
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
    printf("Enter target node: ");
    scanf("%d", &target);

    printf("\nBritish Museum Search (all paths):\n");
    britishMuseumSearch(start, target);

    return 0;
}
