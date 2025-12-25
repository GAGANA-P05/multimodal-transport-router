#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 50
#define INF INT_MAX

typedef struct
{
    int destination;
    int weight;    // Distance
    int eta;       // Expected Time of Arrival
    char mode[10]; // Transport mode (bus, metro, walk)
} Edge;

typedef struct
{
    Edge edges[MAX_NODES];
    int edge_count;
} Node;

Node graph[MAX_NODES];
int node_count;

void add_edge(int src, int dest, int weight, int eta, const char *mode)
{
    int idx = graph[src].edge_count;
    graph[src].edges[idx].destination = dest;
    graph[src].edges[idx].weight = weight;
    graph[src].edges[idx].eta = eta;
    snprintf(graph[src].edges[idx].mode, 10, "%s", mode);
    graph[src].edge_count++;

    // Add reverse edge for bidirectionality
    idx = graph[dest].edge_count;
    graph[dest].edges[idx].destination = src;
    graph[dest].edges[idx].weight = weight;
    graph[dest].edges[idx].eta = eta;
    snprintf(graph[dest].edges[idx].mode, 10, "%s", mode);
    graph[dest].edge_count++;
}

typedef struct
{
    int eta;
    int distance;
    int prev;
    char mode[10];
} DijkstraNode;

void dijkstra(int start, int end)
{
    DijkstraNode dist[MAX_NODES];
    bool visited[MAX_NODES] = {false};

    for (int i = 0; i < node_count; i++)
    {
        dist[i].eta = INF;
        dist[i].distance = INF;
        dist[i].prev = -1;
        strcpy(dist[i].mode, "");
    }

    dist[start].eta = 0;
    dist[start].distance = 0;

    for (int i = 0; i < node_count; i++)
    {
        int min_eta = INF, min_index = -1;
        for (int j = 0; j < node_count; j++)
        {
            if (!visited[j] && dist[j].eta < min_eta)
            {
                min_eta = dist[j].eta;
                min_index = j;
            }
        }

        if (min_index == -1)
            break;
        visited[min_index] = true;

        for (int j = 0; j < graph[min_index].edge_count; j++)
        {
            Edge edge = graph[min_index].edges[j];
            int new_eta = dist[min_index].eta + edge.eta;
            int new_distance = dist[min_index].distance + edge.weight;

            if (new_eta < dist[edge.destination].eta)
            {
                dist[edge.destination].eta = new_eta;
                dist[edge.destination].distance = new_distance;
                dist[edge.destination].prev = min_index;
                snprintf(dist[edge.destination].mode, 10, "%s", edge.mode);
            }
        }
    }

    if (dist[end].eta == INF)
    {
        printf("No path found from node %d to node %d.\n", start, end);
        return;
    }

    printf("\nFastest route from node %d to node %d:\n", start, end);
    printf("    ETA: %d minutes\n", dist[end].eta);
    printf("    Total Distance: %d units\n", dist[end].distance);
    printf("Path: ");

    int current = end, path[MAX_NODES], path_length = 0;
    char modes[MAX_NODES][10];

    while (current != -1)
    {
        path[path_length] = current;
        strcpy(modes[path_length], dist[current].mode);
        path_length++;
        current = dist[current].prev;
    }

    for (int i = path_length - 1; i >= 0; i--)
    {
        if (i < path_length - 1)
            printf(" -> (%s) -> ", modes[i]);
        printf("%d", path[i]);
    }
    printf("\n");
}

int main()
{
    node_count = 20;

    // Initialize graph
    for (int i = 0; i < MAX_NODES; i++)
        graph[i].edge_count = 0;

    // **Complex Graph with Intersections**
    add_edge(0, 1, 5, 10, "bus");
    add_edge(0, 1, 5, 15, "walk");
    add_edge(0, 2, 7, 15, "walk");
    add_edge(0, 2, 7, 7, "bus");
    add_edge(1, 3, 6, 8, "metro");
    add_edge(1, 3, 6, 15, "bus");
    add_edge(1, 4, 8, 12, "bus");
    add_edge(1, 4, 8, 19, "metro");
    add_edge(2, 5, 5, 9, "metro");
    add_edge(2, 5, 5, 17, "walk");
    add_edge(3, 6, 4, 7, "bus");
    add_edge(3, 6, 4, 17, "metro");
    add_edge(3, 6, 4, 27, "walk");
    add_edge(3, 7, 10, 15, "walk");
    add_edge(3, 7, 10, 10, "bus");
    add_edge(4, 8, 5, 20, "metro");
    add_edge(4, 8, 5, 30, "bus");
    add_edge(4, 8, 5, 40, "walk");
    add_edge(5, 9, 7, 12, "bus");
    add_edge(5, 9, 7, 6, "metro");
    add_edge(6, 10, 8, 10, "metro");
    add_edge(6, 10, 8, 5, "bus");
    add_edge(7, 11, 12, 20, "bus");
    add_edge(8, 12, 6, 19, "metro");
    add_edge(8, 12, 6, 9, "bus");
    add_edge(9, 13, 7, 11, "bus");
    add_edge(10, 14, 5, 8, "metro");
    add_edge(10, 14, 5, 28, "bus");
    add_edge(11, 15, 10, 18, "bus");
    add_edge(12, 16, 9, 14, "bus");
    add_edge(12, 16, 9, 24, "metro");
    add_edge(13, 17, 6, 10, "metro");
    add_edge(14, 18, 7, 12, "bus");
    add_edge(15, 19, 8, 30, "metro");
    add_edge(15, 19, 8, 20, "bus");
    add_edge(15, 19, 8, 45, "walk");

    // Extra intersections for complexity
    add_edge(4, 9, 9, 13, "bus");
    add_edge(5, 10, 7, 9, "metro");
    add_edge(6, 11, 6, 8, "walk");
    add_edge(7, 12, 5, 7, "metro");
    add_edge(8, 13, 10, 16, "bus");
    add_edge(9, 14, 8, 11, "metro");
    add_edge(10, 15, 7, 10, "bus");
    add_edge(11, 16, 9, 12, "metro");
    add_edge(12, 17, 8, 10, "bus");
    add_edge(13, 18, 7, 9, "metro");
    add_edge(14, 19, 6, 8, "bus");

    int start, end;
    printf("Enter the source node (0-19): ");
    scanf("%d", &start);
    printf("Enter the destination node (0-19): ");
    scanf("%d", &end);

    if (start < 0 || start >= node_count || end < 0 || end >= node_count)
    {
        printf("Invalid node numbers! Please choose between 0 and 19.\n");
        return 1;
    }

    dijkstra(start, end);
    return 0;
}
