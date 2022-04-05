#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "error_codes.h"
#include "graph.h"
#include "priority_queue.h"
#include "reader.h"
#include "dijkstra.h"

void print_distances_arr(double * arr, int n) {
    for(int i = 0; i < n; i++)
        printf("%d: %f\n", i, arr[i]);
}

// finds shortest path betweent given vertices
// returns shortest path lenght or DBL_MAX when there is no path between given vertices
double dijkstra(graph_t * graph, int begin, int end) {
    
    // ??? checking if begin and end values are correct should happen here or in main.c ?
    
    int i;          // iterator
    double result;  // shortest path between given vertices

    pair_t current;     // the vertex from which the paths are examined
    pair_t examined;    // the vertex to which examined path leads
    long double new_distance;    // potential new distance between current and examined

    double * distance = malloc(sizeof(double) * graph->nodes);  // currently known shortest paths lengths
    int * seen = malloc(sizeof(int) * graph->nodes);            // for marking examined vertices
    int * prev = malloc(sizeof(int) * graph->nodes);            // vertex through which the shortest path leads

    pq_t * pq = init_pq();      // priority queue used in algorithm

    if(distance == NULL || seen == NULL || prev == NULL) {
        fprintf(stderr, "dijkstra(): allocation failed!\n");
        exit(DIJKSTRA_FAILED_ALLOC);
    }

    // fill arrays with default values
    for(i = 0; i < graph->nodes; i++) {
        distance[i] = FLT_MAX;
        seen[i] = UNSEEN;
        prev[i] = PREV_UNKNOWN;
    }

    // add pair (0, begin) to pq
    add_to_pq(pq, 0.0, begin);

    // set values for firs node
    distance[begin] = 0.0;
    seen[begin] = SEEN;

    result = DBL_MAX;

    // dijkstras algorithm
    do {
        current = get_from_pq(pq);
        for(i = 0; i < ADJ_LIST_COLS; i++) {            // examine adjacent vertices
            examined = graph->edge[current.node][i];    // take neighbour of current node
            if(examined.node == DEFAULT_NODE || seen[examined.node] == SEEN) {    // if there is no connection or node was examined continue 
                printf("continued!");
                continue;
            }

            new_distance = distance[current.node] + examined.weight;    // set potential new distance to examined node
            if(distance[examined.node] > new_distance) {                // check if potential new distance is less than currently known one
                printf("tests!");
                distance[examined.node] = new_distance;                     // yes - save new distance to known distances array
                add_to_pq(pq, new_distance, examined.node);                 // add examined node and its new distance to pq
                prev[examined.node] = current.node;                         // set previous node through shortest path leads by
                seen[examined.node] = SEEN;                                 // set flag that examined node was seen

                if(examined.node == end) {
                    return examined.weight;
                }
            }
        }
        printf("\n");

        current = get_from_pq(pq);      // take node with the smallest weight from pq
    } while(!is_empty(pq) && current.node != end); // while pq is not empty and end node is not reached

    result = distance[current.node];
    print_distances_arr(distance, graph->nodes);

    free(distance);
    free(seen);
    free(prev);
    free_pq(pq);

    return result;
}

int main(int argc, char **argv) {
    graph_t * graph = read_from_file("data/graph1");
    show_graph(graph, stdout);
    printf("shortest path: %g\n", dijkstra(graph, atoi(argv[1]), atoi(argv[2])));
    return 0;
}