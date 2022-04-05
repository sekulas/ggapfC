#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"
#include "error_codes.h"

// initializes pq
// returns poiter to initialized priority queue on success and error code to shell in other case
pq_t * init_pq() {
    // priority queue structure allocation
    pq_t * pq = malloc(sizeof(pq_t));
    if(pq == NULL) {
        fprintf(stderr, "init_pq(): pq allocation failed\n");
        exit(PQ_FAILED_ALLOC);
    }

    // array of pairs allocation
    pq->pairs = malloc(sizeof(pair_t) * PQ_START_SIZE);
    if(pq->pairs == NULL) {
        fprintf(stderr, "init_pq(): pairs allocation failed\n");
        exit(PQ_FAILED_ALLOC);
    }

    pq->size = 0;
    pq->capacity = PQ_START_SIZE;

    return pq;
}

// frees memory used by priority queue
void free_pq(pq_t * pq) {
    free(pq->pairs);
    free(pq);
}

// expands pririty queue - reallocation mechanism
// returns pointer to reallocated pq on success and error code to shell in other case
pq_t * expand_pq(pq_t * pq) {
    //printf("reallocation!\n"); // for tests

    int new_capacity = pq->capacity + PQ_START_SIZE;
    pq->pairs = realloc(pq->pairs, sizeof(pair_t) * new_capacity);
    if(pq->pairs == NULL) {
        fprintf(stderr, "expand_pq(): reallocation failed\n");
        exit(PQ_FAILED_REALLOC);
    }

    pq->capacity = new_capacity;
    return pq;
}

// returns true (1) when pq is empty
int is_empty(pq_t * pq) {
    if(pq->size == 0) return 1;
    else return 0;
}

// polls and returns pair with the smallest weight from pq (root)
// returns (-1, -1) when pq is empty
pair_t get_from_pq(pq_t * pq) {
    pair_t taken_off = (pair_t){-1.0, -1};  // (pair_t){weight, node}
    if(is_empty(pq)) return taken_off;      // when pq is empty return default values
    taken_off = pq->pairs[0];               // take root element
    pq->pairs[0] = pq->pairs[--pq->size];   // replace root by last element

    bubble_down(pq);                        // bubble down new root

    return taken_off;
}

// adds pair to pq
// returns 1 on success and error code to shell in other case
int add_to_pq(pq_t * pq, double weight, int node) {
    if(pq->size == pq->capacity)
        pq = expand_pq(pq);

    if(pq == NULL) {
        fprintf(stderr, "add_to_pq(): error: pq is NULL\n");
        exit(PQ_IS_NULL);
    }

    pq->pairs[pq->size].weight = weight;
    pq->pairs[pq->size].node = node;
    pq->size++;

    bubble_up(pq);
    
    return 1;
}

// returns true (value > 0) when p1 < p2 and false in other case
int is_less(pq_t * pq, int p1, int p2) {
    return pq->pairs[p1].weight < pq->pairs[p2].weight;
}

// swaps p1 with p2
void swapp(pq_t * pq, int p1, int p2) {
    pair_t tmp = pq->pairs[p1];
    pq->pairs[p1] = pq->pairs[p2];
    pq->pairs[p2] = tmp;
}

// moves element up to its right place
void bubble_up(pq_t * pq) {
    int current = pq->size - 1;
    int parent = (current - 1) / 2;

    while(current > 0 && is_less(pq, current, parent)) {
        // swapping elements
        swapp(pq, current, parent);

        current = parent;
        parent = (current - 1) / 2;
    }
}

// moves element down to its right place
void bubble_down(pq_t * pq) {
    int n = 0;  // starts from root element
    int left_child, right_child, smallest_child;

    while(1) {
        left_child = (2 * n) + 1;
        right_child = (2 * n) + 2;
        smallest_child = left_child;

        // checking which child is smaller
        if(right_child < pq->size && is_less(pq, right_child, left_child))
            smallest_child = right_child;
        // checking if swapping is needed
        if(left_child >= pq->size || is_less(pq, n, smallest_child))
            break;

        swapp(pq, n, smallest_child);
        n = smallest_child;
    }
}

// shows pq for tests
// mechanism of showing pq diagram needs some improvements
void show_pq(pq_t * pq) {
    if(pq->size > 30) {
        printf("show_pq(): pq too big to dispaly\n");
        return;
    }

    int spaces = 50;
    if(pq == NULL || pq->size == 0) {
        printf("show_pq(): priority queue is empty or NULL\n");
        return;
    }
    int row = 2;
    for(int i = 0; i < pq->size; i++) {
        for(int j = 0; j < spaces - 7; j++)
            printf(" ");
        printf("|%g|", pq->pairs[i].weight);
        if(i + 2 == row) {
            printf("\n");
            spaces = (spaces * 2) / 3;
            row *= 2;
        }
    }
    printf("\n");
}