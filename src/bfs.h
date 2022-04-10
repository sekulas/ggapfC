#ifndef _BFS_H_
#define _BFS_H_
#include "queue.h"
#include "graph.h"


#define CONNECTED_GRAPH 0       //Connected Graph return value for bfs()
#define NOT_CONNECTED_GRAPH 1   //Not Connected Graph return value for bfs()
#define SEEN_NODE '1'           //1 if node has been seen in seen array
#define UNSEEN_NODE '0'         //0 if node has not been seen in seen array

//bfs - returns 0 if graphs is connected, 1 if not
int bfs (graph_t * graph, int node);

//function which jumps into a note (necessary for bfs)
void jump_into(graph_t * graph, int starting_node, queue_ptr_t q);

//returns 0 if graph is connected or 1 if graph is not connected
int is_graph_connected(graph_t * graph, char * seen);

#endif