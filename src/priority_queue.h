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
// returns poiter to initialized priority queue on success and error code to shell in other casee
pq_t * init_pq();

// frees memory used by priority queue
void free_pq(pq_t *);

// expands pririty queue - reallocation mechanism
// returns pointer to reallocated pq on success and error code to shell in other case
pq_t * expand_pq(pq_t*);

// polls and returns pair with the smallest weight from pq (root)
// returns (-1, -1) when pq is empty
pair_t get_from_pq(pq_t*);

// adds pair to pq
// returns 1 on success and error code to shell in other case
int add_to_pq(pq_t*, double, int);

// returns true (value > 0) when p1 < p2 and false (0) in other case
int is_less(pq_t*, int, int);

// swaps p1 with p2
void swapp(pq_t*, int, int);

// moves element up to its right place
void bubble_up(pq_t*);

// moves element down to its right place
void bubble_down(pq_t*);

// shows pq
void show_pq(pq_t*);

#endif