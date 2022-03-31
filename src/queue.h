#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

//queue base
typedef struct node {
    int node;
    struct node * next;
} queue, *queue_p;

//add node to the queue
queue * queue_add(queue_p q, int node);

//returns first node from the queue
int queue_top(queue_p q);

//deletes first element from the queue, returns pointer to the second one
queue * queue_pop(queue_p q);

#endif