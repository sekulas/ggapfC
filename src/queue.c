#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//add node to the queue
queue * queue_add(queue_p q, int node) {
    
    //new element allocation
    queue * new = malloc(sizeof(queue));
    new->node = node;
    if(new == NULL) {
        fprintf(stderr, "queue_add(): 'new' allocation failed\n");
        return NULL;
    }

    queue * iterator = q;

    //empty queue moment
    if(iterator == NULL) {
        return new;
    } 

    //going to the end of the list
    while(iterator->next != NULL)
        iterator = iterator->next;

    iterator->next = new;

    return q;

}

//returns top element from the queue
int queue_top(queue_p q) {
    return q->node;
}

//deletes first element from the queue, returns pointer to the second one
queue * queue_pop(queue_p q) {

    //only one element in the queue moment
    if(q->next == NULL) {
        free(q);
        return NULL;
    }
    
    queue * iterator = q->next;

    free(q);

    return iterator;

}