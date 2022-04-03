#ifndef _QUEUE_H_
#define _QUEUE_H_
//queue base

/* 
konwencja w C jest taka ze przy zdefiniowanych typach daje sie _t
tzn pasowaloby zamienic queue na queue_t i queue_p na np queue_ptr_t
* poprawilem ifndef
*/

typedef struct node {
    int node;
    struct node * next;
} queue, *queue_p;

//IMPORTANT NOTE: Note that queue_add and queue_p returns a queue_p pointer

//add node to the queue
queue_p queue_add(queue_p q, int node);

//returns first node from the queue
int queue_top(queue_p q);

//deletes first element from the queue, returns pointer to the second one
queue_p queue_pop(queue_p q);

#endif