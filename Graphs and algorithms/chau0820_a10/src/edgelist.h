/**
 * -------------------------------------
 * @file  edgelist.h
 * Assignment 10
 * -------------------------------------
 * @author
 *
 * @version 2024-02-25
 *
 * -------------------------------------
 */
#ifndef EDGELIST_H
#define EDGELIST_H

typedef struct edgenode {
  int from;
  int to;
  int weight;
  struct edgenode *next;
} EDGENODE;


typedef struct edgelist {
  int size;
  EDGENODE *start;
  EDGENODE *end;
} EDGELIST;

EDGELIST *new_edgelist();

void insert_edge_start(EDGELIST *g, int from, int to, int weight);

void insert_edge_end(EDGELIST *g, int from, int to, int weight);

void delete_edge(EDGELIST *g, int from, int to);

int weight_edgelist(EDGELIST *g);

void clean_edgelist(EDGELIST **gp);

void display_edgelist(EDGELIST *g);

#endif
