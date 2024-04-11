/*
 * your program signature
 */ 

#include <stdio.h>
#include "queue.h"

/* 
 * Enqueue a node into a queue
 * @param *qp - pointer to the queue 
 * @param NODE *np - pointer to the node.
*/
void enqueue(QUEUE *qp, NODE *np) {
    if (qp->front == NULL){
        qp->rear= np;
        qp->front = qp->rear;
    } else {
        qp->rear->next = np;
        qp->rear= np;
    }
    qp->length++;
}  

/* 
 * Dequeue and return the pointer of the removed node. 
 * @param *qp - pointer to the queue
 * @return - the reference of the removed node, and set it's next to NULL 
*/
NODE *dequeue(QUEUE *qp) {
    NODE *node = qp->front;
    qp->front = qp->front->next;

    if (qp->front == NULL){
        qp->rear = qp->front;
    }

    node->next = NULL;
    qp->length--;
    return node;

}

void clean_queue(QUEUE *qp) {
  clean(&(qp->front));
  qp->front = NULL;
  qp->rear = NULL;
  qp->length=0;
}