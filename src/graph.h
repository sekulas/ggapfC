#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>  // FILE

#define ADJ_LIST_COLS   4       // every node has max 4 connections with others
#define GRAPH_MIN_ROWS  1       // min rows number
#define GRAPH_MIN_COLS  1       // min cols number
#define GRAPH_MAX_ROWS  5000    // max rows number
#define GRAPH_MAX_COLS  5000    // max cols number

#define DEFAULT_WEIGHT  -1.0    // default weight for unused edge
#define DEFAULT_NODE    -1      // default node number for unused edge

#define GRAPH_MAX_NODES (GRAPH_MAX_ROWS * GRAPH_MAX_COLS)   // max nodes in graph

// stores pairs (weight, node) used in Dijkstra algorithm and priority queue
typedef struct pair {
    double weight;  // -1 by default
    int node;       // -1 by default
} pair_t;

typedef struct graph {
    pair_t **edge;
    int rows;
    int columns;
    int nodes;  // number of nodes in graph (rows * cols)
    // ??? int subgraphs;
} graph_t;

// prints graph to chosen stream
void show_graph(graph_t * graph, FILE * out);

// fills weights and nodes with default values
void fill_with_default(graph_t * graph);

// adds edge between nodes to adjacency list
void add_edge(graph_t * graph, int from_node, int to_node, double weight);

// check if given graph size is correct
void validate_graph_size(int rows, int columns);

// frees memory used by graph
void free_graph(graph_t * graph);

// initializes graph
// returns poiter to initialized graph on success and error code to shell in other case
graph_t * init_graph(int rows, int columns);

// generates double value from given range with 2 decimal places
double rand_from_range(double start, double stop);

// generates graph with the given parameters
// returns pointer to graph structure on success end error code to shell in other case
// does not provide validation of parameters!
graph_t * generator(int rows, int columns, double from_weight, double to_weight);

#endif