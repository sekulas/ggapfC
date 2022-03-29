#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include "graph.h"

#define PQ_START_SIZE 8 // temporarily 8, check how many realloactions needed

// stores priority queue
typedef struct PQ {
    pair_t *pairs;
    int size;
    int capacity;
} pq_t;

// add function declarations here

#endif