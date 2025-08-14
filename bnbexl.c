#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 7
#define MAX_EDGES 20

typedef struct {
    int path[N];
    int pathLen;
    int cost;
} Node;

typedef struct {
    Node nodes[100];
    int size;
} PriorityQueue;

typedef struct {
    int u, v, cost;
} Edge;

Edge edges[MAX_EDGES] = {
    {0,1,3}, {0,2,5}, {1,2,4},
    {2,3,4}, {3,5,6}, {1,4,5}, {4,6,3}
};
int numEdges = 7;
int start = 0, goal = 6;
int visited[N]; // extended list

// Function to add to priority queue (min-heap by cost)
void push(PriorityQueue *pq, Node node) {
    pq->nodes[pq->size++] = node;
    int i = pq->size - 1;
    while (i > 0 && pq->nodes[i].cost < pq->nodes[(i - 1) / 2].cost) {
        Node temp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[(i - 1) / 2];
        pq->nodes[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Node pop(PriorityQueue *pq) {
    Node root = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];
    int i = 0;
    while (1) {
        int smallest = i;
        int left = 2 * i + 1, right = 2 * i + 2;
        if (left < pq->size && pq->nodes[left].cost < pq->nodes[smallest].cost)
            smallest = left;
        if (right < pq->size && pq->nodes[right].cost < pq->nodes[smallest].cost)
            smallest = right;
        if (smallest != i) {
            Node temp = pq->nodes[i];
            pq->nodes[i] = pq->nodes[smallest];
            pq->nodes[smallest] = temp;
            i = smallest;
        } else break;
    }
    return root;
}

int main() {
    int oracleLen;
    printf("Enter known oracle path length (benchmark): ");
    scanf("%d", &oracleLen);

    for (int i = 0; i < N; i++) visited[i] = 0;

    PriorityQueue pq = { .size = 0 };
    Node startNode;
    startNode.path[0] = start;
    startNode.pathLen = 1;
    startNode.cost = 0;
    push(&pq, startNode);

    while (pq.size > 0) {
        Node current = pop(&pq);
        int last = current.path[current.pathLen - 1];

        // If goal reached
        if (last == goal) {
            printf("\nGoal reached! Path: ");
            for (int i = 0; i < current.pathLen; i++)
                printf("%d ", current.path[i]);
            printf("\nTotal Cost: %d\n", current.cost);
            return 0;
        }

        // Extended list check
        if (visited[last]) continue;
        visited[last] = 1;

        // Branching
        for (int i = 0; i < numEdges; i++) {
            if (edges[i].u == last || edges[i].v == last) {
                int neighbor = (edges[i].u == last) ? edges[i].v : edges[i].u;
                if (!visited[neighbor]) {
                    int newCost = current.cost + edges[i].cost;

                    // Prune if exceeds oracle benchmark
                    if (newCost > oracleLen) continue;

                    Node child = current;
                    child.path[child.pathLen++] = neighbor;
                    child.cost = newCost;
                    push(&pq, child);
                }
            }
        }
    }

    printf("\nNo path found within oracle benchmark.\n");
    return 0;
}
