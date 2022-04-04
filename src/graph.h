#ifndef _GRAPH_H_
#define _GRAPH_H_

#define ADJ_LIST_COLS   4       // every node has max 4 connections with others
#define GRAPH_MIN_ROWS  1       // min rows number
#define GRAPH_MIN_COLS  1       // min cols number
#define GRAPH_MAX_ROWS  5000    // max rows number
#define GRAPH_MAX_COLS  5000    // max cols number
#define DEFAULT_WEIGHT  -1.0    // default weight for unused edge
#define DEFAULT_NODE    -1      // default node number for unused edge

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
void show_graph(graph_t *, FILE *);

// adds node to adjacency list
void add_to_graph(graph_t *, int, int, int, double);

// check if given graph size is correct
void validate_graph_size(int, int);

// initializes graph
// returns poiter to initialized graph on success and error code to shell in other case
graph_t * init_graph(int, int);

#endif