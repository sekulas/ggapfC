#ifndef _GRAPH_H_
#define _GRAPH_H_

#define ADJ_LIST_COLS 4     // every node has max 4 connections with others

// stores pairs (weight, node) used in Dijkstra algorithm and priority queue
typedef struct pair {
    double weight;  // -1 by default
    int node;       // -1 by default
} pair_t;

typedef struct graph {
    pair_t **edge;
    int rows;
    int cols;
    // ??? int subgraphs;
} graph_t;

// add function declarations here

#endif