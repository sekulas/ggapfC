#ifndef _READER_H_
#define _READER_H_

#include "graph.h"

#define CR      13  // carriage return
#define LF      10  // line feed

// returns pointer to graph structure on success end error code to shell in other case
graph_t * read_from_file(char * filename);

#endif