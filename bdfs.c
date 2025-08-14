#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int n, e;

typedef struct {
    int nodes[MAX];
    int length;
} Path;

// DFS look-ahead (recursive)
int DFS_Lookahead(int current, int goal, int tempVisited[], Path *path) {
    tempVisited[current] = 1;
    path->nodes[path->length++] = current;

    if (current == goal) return 1;

    for (int v = 0; v < n; v++) {
        if (graph[current][v] && !tempVisited[v]) {
            if (DFS_Lookahead(v, goal, tempVisited, path)) return 1;
        }
    }

    path->length--; // backtrack
    return 0;
}

// Hybrid BFS + DFS
void BFS_DFS_Search(int start, int goal) {
    Path queue[MAX];
    int front = 0, rear = 0;

    Path initial = {{start}, 1};
    queue[rear++] = initial;

    visited[start] = 1;

    while (front < rear) {
        Path currentPath = queue[front++];
        int lastNode = currentPath.nodes[currentPath.length - 1];

        if (lastNode == goal) {
            printf("Best path found: ");
            for (int i = 0; i < currentPath.length; i++)
                printf("%d ", currentPath.nodes[i]);
            printf("\n");
            return;
        }

        // Try DFS lookahead from the first neighbor (fast path)
        for (int v = 0; v < n; v++) {
            if (graph[lastNode][v] && !visited[v]) {
                Path dfsPath = currentPath;
                int tempVisited[MAX] = {0};
                for (int i = 0; i < currentPath.length; i++)
                    tempVisited[currentPath.nodes[i]] = 1;

                if (DFS_Lookahead(v, goal, tempVisited, &dfsPath)) {
                    printf("Best path found: ");
                    for (int i = 0; i < dfsPath.length; i++)
                        printf("%d ", dfsPath.nodes[i]);
                    printf("\n");
                    return;
                }
            }
        }

        // Otherwise continue BFS normally
        for (int v = 0; v < n; v++) {
            if (graph[lastNode][v] && !visited[v]) {
                visited[v] = 1;
                Path newPath = currentPath;
                newPath.nodes[newPath.length++] = v;
                queue[rear++] = newPath;
            }
        }
    }

    printf("No path found.\n");
}

int main() {
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Init adjacency matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    int start, goal;
    printf("Enter start node: ");
    scanf("%d", &start);
    printf("Enter goal node: ");
    scanf("%d", &goal);

    BFS_DFS_Search(start, goal);

    return 0;
}
