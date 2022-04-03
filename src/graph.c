#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "error_codes.h"

// initializes graph
// returns poiter to initialized graph on success and error code to shell in other case
graph_t * init_graph(int rows, int cols) {
    int nodes = rows * cols;    // total number of nodes
    int i;

    // graph structure allocation
    graph_t * graph = malloc(sizeof(graph_t));
    if(graph == NULL) {
        fprintf(stderr, "init_graph(): graph allocation failed\n");
        exit(GRAPH_FAILED_ALLOC);
    }

    // adjacency list array allocation
    graph->edge = malloc(sizeof(pair_t*) * nodes);
    if(graph->edge == NULL) {
        fprintf(stderr, "init_graph(): adjacency list allocation failed\n");
        exit(ADJ_LIST_FAILED_ALLOC);
    }

    for(int i = 0; i < nodes; i++) {
        graph->edge[i] = malloc(sizeof(pair_t) * ADJ_LIST_COLS);
        if(graph->edge == NULL) {
            fprintf(stderr, "init_graph(): adjacency list allocation failed\n");
            exit(ADJ_LIST_FAILED_ALLOC);
        }
    }

    /* 
    for example 
        graph->edge[0][1].weight    = 10.0;
        graph->edge[0][1].node      = 3;
    means that we have edge between nodes 0 and 3 with a weight of 10 
    */

    graph->rows = rows;
    graph->cols = cols;

    return graph;
}