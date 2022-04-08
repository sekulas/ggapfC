#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "error_codes.h"

// prints graph to chosen stream
void show_graph(graph_t * graph, FILE * out) {
    // print number of rows and columns
    fprintf(out, "%d %d\n", graph->rows, graph->columns);
    for(int i = 0; i < graph->nodes; i++) {
        for(int j = 0; j < ADJ_LIST_COLS; j++) {
            if(graph->edge[i][j].node == -1) 
                continue; // when there is no edge - contour vertices
            fprintf(out, " %d:%g", graph->edge[i][j].node, graph->edge[i][j].weight);
        }
        fprintf(out, "\n");
    }
}

// fills weights and nodes with default values
void fill_with_default(graph_t * graph) {
    for(int i = 0; i < graph->nodes; i++) {
        for(int j = 0; j < ADJ_LIST_COLS; j++) {
            graph->edge[i][j].node = DEFAULT_NODE;
            graph->edge[i][j].weight = DEFAULT_WEIGHT;
        }
    }
}

// adds node to adjacency list
// modify interface to more intelligent: void add_edge(graph_t * graph, int from, int to, double weight) 
void add_edge(graph_t * graph, int from_node, int to_node, double weight) {
    int i = 0; // iterator

    // check if given node numbers are correct
    if(from_node < 0 || from_node >= graph->nodes || to_node < 0 || to_node >= graph->nodes) {
        fprintf(stderr, "add_to_graph(): index out of range!\n");
        exit(GRAPH_OUT_OF_RANGE);
    }

    // check if weights read from file are correct
    if(weight < 0.0) {
        fprintf(stderr, "add_to_graph(): weight can not be negative!\n");
        exit(GRAPH_CORRUPTED_DATA);
    }

    // add edge to graph
    while(graph->edge[from_node][i].node != DEFAULT_NODE && i < ADJ_LIST_COLS) 
        i++;
    
    if(i < ADJ_LIST_COLS) {
        graph->edge[from_node][i].node = to_node;
        graph->edge[from_node][i].weight = weight;
    } else {
        fprintf(stderr, "add_to_graph(): weight can not be negative!\n");
        exit(GRAPH_TOO_MUCH_EDGES);
    }
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

// frees memory used by graph
void free_graph(graph_t * graph) {
    for(int i = 0; i < graph->nodes; i++)
        free(graph->edge[i]);
    free(graph->edge);
    free(graph);
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
    fill_with_default(graph);   // filling graph with default values

    return graph;
}

// generates graph with the given parameters
// returns pointer to graph structure on success end error code to shell in other case
// does not provide validation of parameters!
graph_t * generator(int rows, int columns, double from_weight, double to_weight) {
    // parameters above should be validated in main.c

    double weight;  // weight read from file
    int i, j;       // indexes of current node in adj list
    graph_t * graph;    // pointer to graph structure

    //printf("%d %d\n", rows, columns); // for tests
    graph = init_graph(rows, columns);

    i = j = 0;
    for(i = 0; i < graph->rows; i++) {
        for(j = 0; j < graph->columns; j++) {
            ;
        }
    }
    
    return graph;
}