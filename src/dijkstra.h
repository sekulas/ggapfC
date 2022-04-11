#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include "priority_queue.h"
#include "graph.h"

#define SEEN            1
#define UNSEEN          0
#define PREV_UNKNOWN   -1
#define BASIC_DIJKSTRA  0


// shows the course of the shortest path
void backtrace(double * distance, int * prev, int begin, int end);

// finds shortest path betweent given vertices
// returns shortest path lenght or DBL_MAX when there is no path between given vertices
// if show_backtrace != 0, the course of the shortest path will be presented
double dijkstra(graph_t * graph, int begin, int end, int show_backtrace, int * prev, int mode);

#endif