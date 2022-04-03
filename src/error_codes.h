#ifndef _ERROR_CODES_H_
#define _ERROR_CODES_H_

/*
Errors prefixes for modules:
    1 - main
    2 - reader
    3 - splitter
    4 - writer
    5 - dijkstra
    6 - bfs
    7 - priority queue
    8 - queue
    9 - graph
*/

#define PQ_FAILED_ALLOC         70
#define PQ_FAILED_REALLOC       71
#define PQ_IS_NULL              72

#define GRAPH_FAILED_ALLOC      90
#define ADJ_LIST_FAILED_ALLOC   91

#endif