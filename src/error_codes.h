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

#define INVALID_FLAG            10
#define LACK_OF_B_OR_E_FLAG     11
#define WRONG_WAGES             12
#define CANNOT_DIVIDE           13
#define BAD_PARAMETERS          14
#define CANNOT_ACCESS_OUT       15

#define READER_CANNOT_OPEN_SRC  20
#define READER_WRONG_FORMAT     21

#define WRITER_CANNOT_CREATE_FILE 40

#define DIJKSTRA_FAILED_ALLOC   50
#define DIJKSTRA_NULL_GRAPH     51
#define DIJKSTRA_OUT_OF_RANGE   52

#define SEEN_FAILED_ALLOC       60

#define PQ_FAILED_ALLOC         70
#define PQ_FAILED_REALLOC       71
#define PQ_IS_NULL              72

#define Q_FAILED_ALLOC          80

#define GRAPH_FAILED_ALLOC      90
#define ADJ_LIST_FAILED_ALLOC   91
#define GRAPH_WRONG_ROW_NUMBER  92
#define GRAPH_WRONG_COL_NUMBER  93
#define GRAPH_OUT_OF_RANGE      94
#define GRAPH_CORRUPTED_DATA    95
#define GRAPH_TOO_MUCH_EDGES    96

#endif