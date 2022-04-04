#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "error_codes.h"

// prints graph to chosen stream
void show_graph(graph_t * graph, FILE * out) {
    // print number of rows and columns
    fprintf(out, "%d %d\n", graph->rows, graph->columns);
    for(int i = 0; i < graph->nodes; i++) {
        for(int j = 0; j < 4; j++) {
            if(graph->edge[i][j].node == -1) 
                continue; // when there is no edge - contour vertices
            fprintf(out, " %d:%g", graph->edge[i][j].node, graph->edge[i][j].weight);
        }
        fprintf(out, "\n");
    }
}

// adds node to adjacency list
void add_to_graph(graph_t * graph, int i, int j, int node, double weight) {
    // check if adj list indexes are correct
    if(i >= graph->nodes || j >= 4) {
        fprintf(stderr, "add_to_graph(): index out of range!\n");
        exit(GRAPH_OUT_OF_RANGE);
    }

    // check if data read from file is correct
    if(node >= graph->nodes || weight < 0.0) {
        fprintf(stderr, "add_to_graph(): nodes out of rangE or negative weights!\n");
        exit(GRAPH_CORRUPTED_DATA);
    }

    // add edge to graph
    graph->edge[i][j].node = node;
    graph->edge[i][j].weight = weight;
}

// check if given graph size is correct
void validate_graph_size(int rows, int columns) {
    if(rows < GRAPH_MIN_ROWS || rows > GRAPH_MAX_ROWS) {
        fprintf(stderr, "validate_graph_size(): wrong number of rows!\n");
        exit(GRAPH_WRONG_ROW_NUMBER);
    }

    if (columns < GRAPH_MIN_COLS || columns > GRAPH_MAX_COLS) {
        fprintf(stderr, "validate_graph_size(): wrong number of columns!\n");
        exit(GRAPH_WRONG_COL_NUMBER);
    }
}

// initializes graph
// returns poiter to initialized graph on success and error code to shell in other case
graph_t * init_graph(int rows, int columns) {
    int nodes;  // total number of nodes
    int i;      // iterator
    graph_t * graph;    // graph structure

    validate_graph_size(rows, columns);
    nodes = rows * columns;

    // graph structure allocation
    graph = malloc(sizeof(graph_t));
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
    graph->columns = columns;
    graph->nodes = nodes;

    return graph;
}