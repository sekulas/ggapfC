#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

// initializes pq
// returns poiter to initialized priority queue on success and NULL in other case
pq_t * init_pq() {
    pq_t * pq = malloc(sizeof(pq) * PQ_START_SIZE);
    if(pq == NULL) {
        printf("priority_queue: allocation failed\n");
        return NULL;
    }

    pq->size = 0;
    pq->capacity = PQ_START_SIZE;

    return pq;
}

pq_t expand_pq() {
    // reallocation mechanism
}