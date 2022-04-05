#ifndef _QUEUE_H_
#define _QUEUE_H_
//queue base

/* 
konwencja w C jest taka ze przy zdefiniowanych typach daje sie _t
tzn pasowaloby zamienic queue na queue_t i queue_ptr_t na np queue_ptr_ttr_t
* poprawilem ifndef
*/

typedef struct node {
    int node;
    struct node * next;
} queue_t, *queue_ptr_t;

//IMPORTANT NOTE: Note that queue_add and queue_ptr_t returns a queue_ptr_t pointer

//add node to the queue
queue_ptr_t queue_add(queue_ptr_t q, int node);

//returns first node from the queue
int queue_top(queue_ptr_t q);

//deletes first element from the queue, returns pointer to the second one
queue_ptr_t queue_pop(queue_ptr_t q);

#endif