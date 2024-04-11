/**
 * -------------------------------------
 * @file  graph.c
 * Assignment 10
 * -------------------------------------
 * @author
 *
 * @version 2024-02-25
 *
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_stack.h"
#include "graph.h"

GRAPH *new_graph(int order) {
  GRAPH *gp = malloc(sizeof(GRAPH));
  gp->nodes = malloc(order * sizeof(GNODE*));
  int i;
  for (i = 0; i < order; i++) {
    gp->nodes[i] = malloc(sizeof(GNODE));
    gp->nodes[i]->nid = i;
    strcpy(gp->nodes[i]->name, "null");
    gp->nodes[i]->neighbor = NULL;
  }

  gp->order = order;
  gp->size = 0;

  return gp;
}

void insert_edge_graph(GRAPH *g, int from, int to, int weight) {
	ADJNODE *new_node = malloc(sizeof(ADJNODE));
	    new_node->nid = to;
	    new_node->weight = weight;
	    new_node->next = g->nodes[from]->neighbor;
	    g->nodes[from]->neighbor = new_node;
	    g->size++;
	}

void delete_edge_graph(GRAPH *g, int from, int to) {
	ADJNODE *current = g->nodes[from]->neighbor;
	    ADJNODE *previous = NULL;

	    while (current != NULL) {
	        if (current->nid == to) {
	            if (previous == NULL) {
	                g->nodes[from]->neighbor = current->next;
	            } else {
	                previous->next = current->next;
	            }
	            free(current);
	            g->size--;
	            return;
	        }
	        previous = current;
	        current = current->next;
	    }
	}

int get_edge_weight(GRAPH *g, int from, int to) {
	ADJNODE *current = g->nodes[from]->neighbor;

	    while (current != NULL) {
	        if (current->nid == to) {
	            return current->weight;
	        }
	        current = current->next;
	    }

	    return -1;
	}

void traverse_bforder(GRAPH *g, int nid) {
	int *visited = calloc(g->order, sizeof(int));
	    QUEUE q;
	    q.front = q.rear = NULL;

	    int *startNode = malloc(sizeof(int));
	    *startNode = nid;
	    enqueue(&q, startNode);
	    visited[nid] = 1;

	    while (q.front != NULL) {
	        int *currentNode = dequeue(&q);
	        int current = *currentNode;
	        free(currentNode);

	        printf("%d ", current);

	        for (ADJNODE *ptr = g->nodes[current]->neighbor; ptr != NULL; ptr = ptr->next) {
	            if (!visited[ptr->nid]) {
	                int *nextNode = malloc(sizeof(int));
	                *nextNode = ptr->nid;
	                enqueue(&q, nextNode);
	                visited[ptr->nid] = 1;
	            }
	        }
	    }

	    free(visited);
	    clean_queue(&q);
	}

// Use auxiliary stack data structure for the algorithm
void traverse_dforder(GRAPH *g, int nid) {
	int *visited = calloc(g->order, sizeof(int));
	    STACK s;
	    s.top = NULL;

	    int *startNode = malloc(sizeof(int));
	    *startNode = nid;
	    push(&s, startNode);

	    while (s.top != NULL) {
	        int *currentNode = pop(&s);
	        int current = *currentNode;
	        free(currentNode);

	        if (!visited[current]) {
	            printf("%d ", current);
	            visited[current] = 1;

	            for (ADJNODE *ptr = g->nodes[current]->neighbor; ptr != NULL; ptr = ptr->next) {
	                if (!visited[ptr->nid]) {
	                    int *nextNode = malloc(sizeof(int));
	                    *nextNode = ptr->nid;
	                    push(&s, nextNode);
	                }
	            }
	        }
	    }

	free(visited);
	clean_stack(&s);
	}

void clean_graph(GRAPH **gp) {
  int i;
  GRAPH *g = *gp;
  ADJNODE *temp, *ptr;
  for (i = 0; i < g->order; i++) {
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      temp = ptr;
      ptr = ptr->next;
      free(temp);
    }
    free(g->nodes[i]);
  }
  free(g->nodes);
  free(g);
  *gp = NULL;
}

void display_graph(GRAPH *g) {
  if (g ) {
  printf("order %d ", g->order);
  printf("size %d ", g->size);
  printf("(from to weight) ");
  int i;
  ADJNODE *ptr;
  for (i = 0; i < g->order; i++) {
    //printf("\n%d:", g->nodes[i]->nid);
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      printf("(%d %d %d) ", i,  ptr->nid, ptr->weight);
      ptr = ptr->next;
    }
  }
  }
}
