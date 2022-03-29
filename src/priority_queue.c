#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

// initializes pq
// returns poiter to initialized priority queue on success and NULL in other case
pq_t * init_pq() {
    pq_t * pq = malloc(sizeof(pq));
    pq->pairs = malloc(sizeof(pq->pairs) * PQ_START_SIZE);
    if(pq == NULL || pq->pairs == NULL) {
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
    pq->pairs = realloc(pq->pairs, sizeof(pq->pairs) * new_capacity);
    if(pq->pairs == NULL) {
        fprintf(stderr, "priority_queue: reallocation failed\n");
        pq->size = 0;
        pq->capacity = 0;
        return NULL;
    }

    pq->capacity = new_capacity;
}

// polls and returns pair with the smallest weight from pq (root)
// returns (-1, -1) when pq is empty
pair_t get_from_pq(pq_t * pq) {
    if(pq->size == 1) return (pair_t){-1.0, -1};
    pair_t pair = pq->pairs[0];
    pq->pairs[0] = pq->pairs[--pq->size];

    bubble_down(pq);

    return pair;
}

// adds pair to pq
// returns 1 on success and 0 in the oter case
int add_to_pq(pq_t * pq, double weight, int node) {
    if(pq->size >= pq->capacity)
        if(expand_pq(pq) == NULL)
            return 0;

    pq->pairs[pq->size++] = (pair_t){weight, node};
    bubble_up(pq);
    
    return 1;
}

// moves element up to its right place
void bubble_up(pq_t * pq) {

}

// moves element down to its right place
void bubble_down(pq_t * pq) {
    int n = 0;
    int left_child, right_child;

    while(1) {
        left_child = (2 * n) + 1;
        right_child = (2 * n) + 2;

        // to be continued ...
    }

}