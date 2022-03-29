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

// initializes pq
// returns poiter to initialized priority queue on success and NULL in other case
pq_t * init_pq();

// expands pririty queue - reallocation mechanism
// returns pointer to reallocated pq on success and NULL in other case
pq_t * expand_pq(pq_t*);

// polls and returns pair with the smallest weight from pq (root)
// returns (-1, -1) when pq is empty
pair_t get_from_pq(pq_t*);

// adds pair to pq
// returns 1 on success and 0 in the oter case
int add_to_pq(pq_t*, double, int);

// moves element up to its right place
void bubble_up(pq_t*);

// moves element down to its right place
void bubble_down(pq_t*);

#endif