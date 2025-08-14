#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int graph[MAX][MAX]; // adjacency matrix
bool visited[MAX];
int queue[MAX];
int front = 0, rear = 0;
int parent[MAX]; // to reconstruct path

void enqueue(int v) {
    queue[rear++] = v;
}

int dequeue() {
    return queue[front++];
}

bool isEmpty() {
    return front == rear;
}

void printPath(int start, int goal) {
    if (goal == start) {
        printf("%d ", start);
        return;
    }
    printPath(start, parent[goal]);
    printf("%d ", goal);
}

void BFS(int start, int goal, int nodes) {
    for (int i = 0; i < nodes; i++) visited[i] = false;
    for (int i = 0; i < nodes; i++) parent[i] = -1;

    visited[start] = true;
    enqueue(start);

    while (!isEmpty()) {
        int current = dequeue();

        if (current == goal) { // preemptive exit
            //printf("Goal %d found! Path: ", goal);
            printPath(start, goal);
            printf("\n");
            return;
        }

        for (int i = 0; i < nodes; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = true;
                enqueue(i);
                parent[i] = current;
            }
        }
    }

    printf("Goal not found in the graph.\n");
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

    BFS(start, goal, nodes);

    return 0;
}

/*
0 1
0 2
1 2
2 3
3 5
1 4
4 6
*/