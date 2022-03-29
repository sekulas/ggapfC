#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

// initializes pq
// returns poiter to initialized priority queue on success and NULL in other case
pq_t * init_pq() {
    pq_t * pq = malloc(sizeof(pq) * PQ_START_SIZE);
    if(pq == NULL) {
        fprintf(stderr, "priority_queue: allocation failed\n");
        pq->size = 0;
        pq->capacity = 0;
        return NULL;
    }

    pq->size = 0;
    pq->capacity = PQ_START_SIZE;

    return pq;
}

// expands pririty queue - reallocation mechanism
// returns pointer to reallocated pq on success and NULL in other case
pq_t * expand_pq(pq_t * pq) {
    printf("reallocation!\n"); // for tests
    int new_capacity = pq->capacity + PQ_START_SIZE;
    pq = realloc(pq, sizeof(pq) * new_capacity);
    if(pq == NULL) {
        fprintf(stderr, "priority_queue: reallocation failed\n");
        pq->size = 0;
        pq->capacity = 0;
        return NULL;
    }

    pq->capacity = new_capacity;
}

// polls and returns pair with the smallest weight from pq (root)
// returns (-1, -1) when pq is empty
pq_t get_from_pq(pq_t * pq) {

}

int add_to_pq(pq_t * pq, double weight, int node) {

}

void bubble_up(pq_t * pq) {

}

void bubble_down(pq_t * pq) {
    
}