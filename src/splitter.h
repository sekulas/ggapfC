#ifndef _SPLITTER_H_
#define _SPLITTER_H_

#include "graph.h"

#define EDGE_NODE       1
#define NOT_EDGE_NODE   0
#define SPLIT_MODE      1
#define NOT_SPLIT_MODE  0

//splits our graphs
void splitter(graph_t * graph, char * prev);

//returns info about node ( is it on the edge or not )
int is_on_the_edge(graph_t * graph, int node);

#endif