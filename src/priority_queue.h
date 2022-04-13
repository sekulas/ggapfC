#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include "graph.h"

#define PQ_START_SIZE 32 // temporarily 32, check how many realloactions needed

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
void free_pq(pq_t * pq);

// expands pririty queue - reallocation mechanism
// returns pointer to reallocated pq on success and error code to shell in other case
pq_t * expand_pq(pq_t * pq);

// returns true (1) when pq is empty
int is_empty(pq_t * pq);

// polls and returns pair with the smallest weight from pq (root)
// returns (-1, -1) when pq is empty
pair_t get_from_pq(pq_t * pq);

// adds pair to pq
// returns 1 on success and error code to shell in other case
int add_to_pq(pq_t * pq, double weight, int node);

// returns true (value > 0) when p1 < p2 and false (0) in other case
int is_less(pq_t * pq, int p1, int p2);

// swaps p1 with p2
void swapp(pq_t * pq, int p1, int p2);

// moves element up to its right place
void bubble_up(pq_t * pq);

// moves element down to its right place
void bubble_down(pq_t * pq);

// shows pq
void show_pq(pq_t * pq);

#endif