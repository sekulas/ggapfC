#ifndef _WRITER_H_
#define _WRITER_H_

#include "graph.h"

// prints the graph to the selected file
// when filename is NULL prints to stdout
void save_to_file(graph_t * graph, char * filename);

// prints the graph to the selected file
void save_to_graphml(graph_t * graph, char * filename);

#endif