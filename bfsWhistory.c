#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int queue[MAX], front = 0, rear = 0;
int visited[MAX];
int parent[MAX];

void enqueue(int x) {
    queue[rear++] = x;
}

int dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

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

void BFS(int graph[MAX][MAX], int n, int start, int goal) {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    enqueue(start);
    visited[start] = 1;

    while (!isEmpty()) {
        int node = dequeue();
        
        if (node == goal) {
            reconstructPath(start, goal);
            return; // preemptive exit
        }

        for (int i = 0; i < n; i++) {
            if (graph[node][i] && !visited[i]) {
                visited[i] = 1;
                parent[i] = node;
                enqueue(i);
            }
        }
    }

    printf("No path found\n");
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

    int start, goal;
    printf("Enter start and goal: ");
    scanf("%d %d", &start, &goal);

    BFS(graph, n, start, goal);

    return 0;
}
