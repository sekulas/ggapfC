#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "error_codes.h"

//add node to the queue
queue_ptr_t queue_add(queue_ptr_t q, int node) {
    
    //new element allocation
    queue_ptr_t new = malloc(sizeof(queue_t));
    new->node = node;
    new->next = NULL;
    
    if(new == NULL) {
        fprintf(stderr, "queue_add(): 'new' allocation failed\n");
        exit(Q_FAILED_ALLOC);
    }

    queue_ptr_t iterator = q;

    //empty queue moment
    if(iterator == NULL)
        return new;

    //going to the end of the list
    while(iterator->next != NULL)
        iterator = iterator->next;

    iterator->next = new;

    return q;

}

//returns info about queue being empty (1) or not (0)
int queue_empty(queue_ptr_t q) {
    if(q == NULL)
        return QUEUE_EMPTY;
    
    return QUEUE_NOT_EMPTY;
}
//returns top element from the queue
int queue_top(queue_ptr_t q) {
    return q->node;
}

//deletes first element from the queue, returns pointer to the second one
queue_ptr_t queue_pop(queue_ptr_t q) {

    //only one element in the queue moment
    if(q->next == NULL) {
        free(q);
        return NULL;
    }
    
    queue_ptr_t iterator = q->next;

    free(q);

    return iterator;

}