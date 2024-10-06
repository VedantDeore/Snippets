#include <stdio.h>
#include <limits.h>

#define V 9 // Number of vertices in the graph

// Function to calculate the minimum f(n) value (g(n) + h(n)) in the open set
int minFValue(int f[], int openSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (openSet[v] == 1 && f[v] <= min) {
            min = f[v];
            min_index = v;
        }

    return min_index;
}

// Function to print the shortest path distance and nodes
void printSolution(int dist[], int src, int goal) {
    printf("Shortest path from Vertex %d to Vertex %d is: %d\n", src, goal, dist[goal]);
}

// A* algorithm implementation for a graph represented by an adjacency matrix
void aStar(int graph[V][V], int src, int goal, int heuristic[V]) {
    int g[V]; // g(n): the cost to reach each vertex
    int f[V]; // f(n): the estimated total cost (g(n) + h(n))
    int openSet[V]; // Open set: vertices to be evaluated
    int closedSet[V]; // Closed set: vertices already evaluated

    // Initialize all distances (g) as INFINITE and all f values as INFINITE
    for (int i = 0; i < V; i++) {
        g[i] = INT_MAX;
        f[i] = INT_MAX;
        openSet[i] = 0;
        closedSet[i] = 0;
    }

    // Initialize the source node
    g[src] = 0;
    f[src] = heuristic[src]; // f(n) = g(n) + h(n)
    openSet[src] = 1;

    // Loop to explore the open set
    while (1) {
        // Find the node with the smallest f(n) in the open set
        int current = minFValue(f, openSet);

        // If we reach the goal node or there's no more nodes to process, exit
        if (current == goal || current == -1) {
            printSolution(g, src, goal);
            return;
        }

        // Remove current node from open set and add to closed set
        openSet[current] = 0;
        closedSet[current] = 1;

        // Process all adjacent vertices of the current node
        for (int v = 0; v < V; v++) {
            // If this vertex is already in the closed set, skip it
            if (closedSet[v] || graph[current][v] == 0)
                continue;

            // Calculate tentative g(n) for the adjacent vertex
            int tentative_g = g[current] + graph[current][v];

            // If tentative g(n) is better, update g(n) and f(n)
            if (tentative_g < g[v]) {
                g[v] = tentative_g;
                f[v] = g[v] + heuristic[v]; // f(n) = g(n) + h(n)
                openSet[v] = 1; // Add the node to the open set
            }
        }
    }
}

int main() {
    // Graph represented as an adjacency matrix
    int graph[V][V] = {
        { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
        { 0, 0, 2, 0, 0, 0, 6, 7, 0 }
    };

    // Heuristic values for each node (Manhattan distance or another heuristic)
    int heuristic[V] = {7, 6, 2, 1, 5, 8, 3, 4, 6};

    // Start A* from vertex 0 to vertex 8
    aStar(graph, 0, 8, heuristic);

    return 0;
}
