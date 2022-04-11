#ifndef _SPLITTER_H_
#define _SPLITTER_H_

#include "graph.h"

#define EDGE_NODE       1
#define NOT_EDGE_NODE   0
#define SPLIT_MODE      1
#define NOT_SPLIT_MODE  0
#define UP  0
#define RIGHT 1
#define DOWN 2
#define LEFT  3 
#define EDGE_CASE      0
#define NORMAL_CASE    1

//splits our graphs
void splitter(graph_t * graph, int * primary_prev, char * primary_seen, int starting_node, int end_node);

//direction guesser
int direction( int rows, int columns, int current_node, int following_node );

//returns info about node ( is it on the edge or not )
int is_on_the_edge(graph_t * graph, int node);

#endif