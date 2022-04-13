#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QUEUE_EMPTY 1;
#define QUEUE_NOT_EMPTY 0;
//queue base

typedef struct node {
    int node;
    struct node * next;
} queue_t, *queue_ptr_t;

//IMPORTANT NOTE: Note that queue_add and queue_ptr_t returns a queue_ptr_t pointer

//add node to the queue
queue_ptr_t queue_add(queue_ptr_t q, int node);

//returns info about queue being empty (1) or not (0)
int queue_empty(queue_ptr_t q);

//returns first node from the queue
int queue_top(queue_ptr_t q);

//deletes first element from the queue, returns pointer to the second one
queue_ptr_t queue_pop(queue_ptr_t q);

#endif