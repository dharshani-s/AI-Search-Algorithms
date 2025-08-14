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

// Heuristic values (goal = node 6)
int heuristic[N] = {999, 7, 6, 7, 3, 4, 0};

// Adjacency matrix
int graph[N][N];

typedef struct {
    int node;
    int g; // cost so far
    int f; // g + h
    int parent;
    int visited;
} NodeInfo;

int reconstruct_path(NodeInfo nodes[], int start, int goal, int path[]) {
    int length = 0;
    int current = goal;
    while (current != -1) {
        path[length++] = current;
        current = nodes[current].parent;
    }
    // Reverse path
    for (int i = 0; i < length / 2; i++) {
        int temp = path[i];
        path[i] = path[length - i - 1];
        path[length - i - 1] = temp;
    }
    return length;
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

    NodeInfo nodes[N];
    for (int i = 0; i < N; i++) {
        nodes[i].node = i;
        nodes[i].g = INT_MAX;
        nodes[i].f = INT_MAX;
        nodes[i].parent = -1;
        nodes[i].visited = 0;
    }

    int start = 0, goal = 6;
    nodes[start].g = 0;
    nodes[start].f = heuristic[start];

    while (1) {
        // Find unvisited node with smallest f
        int current = -1, minF = INT_MAX;
        for (int i = 0; i < N; i++) {
            if (!nodes[i].visited && nodes[i].f < minF) {
                minF = nodes[i].f;
                current = i;
            }
        }

        if (current == -1) break; // no more nodes to explore

        if (nodes[current].g > oracleCost) break; // prune if exceeds oracle

        if (current == goal) {
            int path[N];
            int length = reconstruct_path(nodes, start, goal, path);

            printf("\nBest Path Found (A*): ");
            for (int i = 0; i < length; i++) {
                printf("%d", path[i]);
                if (i < length - 1) printf(" -> ");
            }
            printf("\nPath Cost: %d\n", nodes[goal].g);
            return 0;
        }

        nodes[current].visited = 1;

        // Check neighbors
        for (int i = 0; i < N; i++) {
            if (graph[current][i] != 0 && !nodes[i].visited) {
                int tentative_g = nodes[current].g + graph[current][i];
                if (tentative_g < nodes[i].g) {
                    nodes[i].parent = current;
                    nodes[i].g = tentative_g;
                    nodes[i].f = tentative_g + heuristic[i];
                }
            }
        }
    }

    printf("\nNo path found within given oracle bound.\n");
    return 0;
}
