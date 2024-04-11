/**
 * -------------------------------------
 * @file  queue_linked.c
 * Linked Queue Source Code File
 * -------------------------------------
 * @author name, ID, email
 *
 * @version 2024-02-22
 *
 * -------------------------------------
 */
// Includes
#include "queue_linked.h"

// Functions

queue_linked* queue_initialize() {
    // Allocate memory to the queue 
    queue_linked *source = malloc(sizeof *source);
    // Initialize the queue 
    source->front = NULL;
    source->rear = NULL;
    return source;
}

void queue_free(queue_linked **source) {
    // Free the linked data
    while((*source)->front != NULL) {
        queue_node *temp = (*source)->front;
        // use the data_free function to free the actual data
        data_free(&temp->item);
        // update the queue front
        (*source)->front = (*source)->front->next;
        // free the queue node
        free(temp);
        temp = NULL;
    }
    // Free the queue header
    (*source)->rear = (*source)->front;
    free(*source);
    *source = NULL;
    return;
}

BOOLEAN queue_empty(const queue_linked *source) {

    return (source->front == NULL);

}

int queue_count(const queue_linked *source) {

    int count = 0;
    queue_node *temp = source->front;
    while (temp){
        count++;
        temp = temp->next;
    }
    return count;
}

void queue_insert(queue_linked *source, data_ptr item) {

    // allocate memory to a new queue node
    queue_node *node = malloc(sizeof *node);
    // allocate memoory for the data
    node->item = malloc(sizeof *node->item);
    // copy the data parameter to the new memory
    data_copy(node->item, item);

    if (source->rear == NULL){
        source->front= node;
        source->rear = source->front;
        node->next = NULL;
    } else {
        source->rear->next = node;
        node->next = NULL;
        source->rear = node;
    }
    source->count++;

}

BOOLEAN queue_peek(const queue_linked *source, data_ptr item) {

    BOOLEAN peeked = FALSE;

    if(source->front != NULL) {
        // return a copy of the data in the node
        data_copy(item, source->front->item);
        peeked = TRUE;
    }
    return peeked;

}

BOOLEAN queue_remove(queue_linked *source, data_ptr *item) {
    BOOLEAN removed = FALSE;

    if(source->front != NULL) {
        // return a pointer to the node data
        *item = source->front->item;
        queue_node *temp = source->front;
        // update the queue top and free the removed node
        source->front = source->front->next;
        free(temp);
        removed = TRUE;
        source->count--;
    }

    if (source->front == NULL) {
        source->rear = NULL;
    }

    return removed;

}

void queue_print(const queue_linked *source) {
    char string[DATA_STRING_SIZE];
    queue_node *current = source->front;

    while(current != NULL) {
        printf("%s\n", data_string(string, sizeof string, current->item));
        current = current->next;
    }
    return;
}
