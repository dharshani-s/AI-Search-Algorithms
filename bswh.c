#include <stdio.h>
#include <string.h>

#define N 7
#define BEAM_WIDTH 2

// Your graph (undirected), adjacency matrix with 0/1
static int adj[N][N];
// Your heuristic values
static int h[N] = {999, 7, 6, 7, 3, 4, 0};

static int parent[N];   // for path reconstruction
static int closed[N];   // expanded history

// Add undirected edge
void add_edge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;
}

// Reconstruct and print path start->goal using parent[]
void print_path(int start, int goal) {
    int stack[N], top = 0;
    int cur = goal;
    while (cur != -1) {
        stack[top++] = cur;
        cur = parent[cur];
    }
    printf("Path: ");
    for (int i = top - 1; i >= 0; --i) {
        printf("%d", stack[i]);
        if (i) printf(" -> ");
    }
    printf("\n");
}

int main(void) {
    // --- Hardcoded graph from your input ---
    // Nodes: 0..6
    // Edges:
    // 0-1, 0-2, 1-2, 2-3, 3-5, 1-4, 4-6
    memset(adj, 0, sizeof(adj));
    add_edge(0, 1);
    add_edge(0, 2);
    add_edge(1, 2);
    add_edge(2, 3);
    add_edge(3, 5);
    add_edge(1, 4);
    add_edge(4, 6);

    const int start = 0;
    const int goal  = 6;

    // Init
    for (int i = 0; i < N; ++i) { parent[i] = -1; closed[i] = 0; }

    // Beam for current level (nodes only)
    int beam[BEAM_WIDTH], bsz = 1;
    beam[0] = start;

    // Parent of the first layer
    parent[start] = -1;

    // To avoid generating duplicates inside a level
    int in_current[N] = {0};
    in_current[start] = 1;

    // If start is the goal
    if (start == goal) {
        print_path(start, goal);
        return 0;
    }

    while (bsz > 0) {
        // Early goal check in current beam
        for (int i = 0; i < bsz; ++i) {
            if (beam[i] == goal) {
                print_path(start, goal);
                return 0;
            }
        }

        // Collect candidates from expanding all nodes in current beam
        int cand[N], cand_parent[N], csz = 0;
        int in_next[N] = {0};

        for (int i = 0; i < bsz; ++i) {
            int u = beam[i];

            // Expand u; mark it closed (expanded history)
            closed[u] = 1;

            for (int v = 0; v < N; ++v) {
                if (!adj[u][v]) continue;

                // Avoid returning to already expanded nodes or staying in the same beam
                if (closed[v] || in_current[v]) continue;

                // Deduplicate within next level: keep first parent (stable)
                if (!in_next[v]) {
                    in_next[v] = 1;
                    cand[csz] = v;
                    cand_parent[csz] = u;
                    ++csz;

                    // Early-exit if we hit goal; record parent and print path
                    if (v == goal) {
                        parent[v] = u;
                        print_path(start, goal);
                        return 0;
                    }
                }
            }
        }

        // If no candidates, search fails
        if (csz == 0) {
            printf("Goal not found.\n");
            return 0;
        }

        // Pick top BEAM_WIDTH by lowest heuristic; stable selection
        int next_beam[BEAM_WIDTH], nsz = 0;
        int picked[N] = {0};
        for (int k = 0; k < BEAM_WIDTH && k < csz; ++k) {
            int best = -1;
            for (int i = 0; i < csz; ++i) {
                if (picked[i]) continue;
                if (best == -1 || h[cand[i]] < h[cand[best]]) best = i;
            }
            picked[best] = 1;
            next_beam[nsz] = cand[best];

            // Set parent for selected candidate only once
            if (parent[next_beam[nsz]] == -1)
                parent[next_beam[nsz]] = cand_parent[best];

            ++nsz;
        }

        // Prepare next iteration
        memset(in_current, 0, sizeof(in_current));
        bsz = nsz;
        for (int i = 0; i < bsz; ++i) {
            beam[i] = next_beam[i];
            in_current[beam[i]] = 1;
        }
    }

    printf("Goal not found.\n");
    return 0;
}
