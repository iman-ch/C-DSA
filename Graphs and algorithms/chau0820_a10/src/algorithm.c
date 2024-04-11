/**
 * -------------------------------------
 * @file  algorithm.c
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
#include <limits.h>
#include "heap.h"
#include "algorithm.h"
#include "graph.h"
#include "edgelist.h"

EDGELIST *mst_prim(GRAPH *g, int start) {
	HEAP *pq = new_heap(g->order);
	EDGELIST *mst = new_edgelist();
	int *parent = malloc(g->order * sizeof(int));
	int *key = malloc(g->order * sizeof(int));
	int *inMST = calloc(g->order, sizeof(int));

	for (int i = 0; i < g->order; i++) {
	    key[i] = INT_MAX;
	    parent[i] = -1;
	    heap_insert(pq, (HEAPDATA){key[i], i});
	}

	key[start] = 0;
	heap_change_key(pq, start, key[start]);

	while (pq->size != 0) {
	    int u = heap_extract_min(pq).value;
	    inMST[u] = 1;

	    for (ADJNODE *adj = g->nodes[u]->neighbor; adj != NULL; adj = adj->next) {
	        int v = adj->nid;
	        int weight = adj->weight;

	        if (!inMST[v] && weight < key[v]) {
	            key[v] = weight;
	            parent[v] = u;
	            heap_change_key(pq, heap_search_data(pq, v), key[v]);
	        }
	    }
	}

	for (int i = 0; i < g->order; i++) {
	    if (parent[i] != -1) {
	        insert_edge_end(mst, parent[i], i, key[i]);
	    }
	}

	free(parent);
	free(key);
	free(inMST);
	heap_clean(&pq);

	return mst;
	}

EDGELIST *spt_dijkstra(GRAPH *g, int start) {
	int *dist = malloc(g->order * sizeof(int));
	HEAP *pq = new_heap(g->order);
	EDGELIST *spt = new_edgelist();

	for (int i = 0; i < g->order; i++) {
	    dist[i] = INT_MAX;
	    heap_insert(pq, (HEAPDATA){dist[i], i});
	}

	dist[start] = 0;
	heap_change_key(pq, start, dist[start]);

	while (pq->size != 0) {
	    int u = heap_extract_min(pq).value;

	    for (ADJNODE *adj = g->nodes[u]->neighbor; adj != NULL; adj = adj->next) {
	        int v = adj->nid;
	        int weight = adj->weight;

	        if (dist[v] > dist[u] + weight) {
	            dist[v] = dist[u] + weight;
	            heap_change_key(pq, heap_search_data(pq, v), dist[v]);
	            insert_edge_end(spt, u, v, dist[v]);
	        }
	    }
	}

	free(dist);
	heap_clean(&pq);

	return spt;
	}

EDGELIST *sp_dijkstra(GRAPH *g, int start, int end) {
	int *dist = malloc(g->order * sizeof(int));
	int *prev = malloc(g->order * sizeof(int));
	HEAP *pq = new_heap(g->order);
	EDGELIST *path = new_edgelist();

	for (int i = 0; i < g->order; i++) {
	    dist[i] = INT_MAX;
	    prev[i] = -1;
	    heap_insert(pq, (HEAPDATA){dist[i], i});
	}

	dist[start] = 0;
	heap_change_key(pq, heap_search_data(pq, start), dist[start]);

	while (pq->size != 0) {
	    int u = heap_extract_min(pq).value;
		if (u == end) break;

	    for (ADJNODE *adj = g->nodes[u]->neighbor; adj != NULL; adj = adj->next) {
	        int v = adj->nid;
	        int weight = adj->weight;

	        if (dist[u] + weight < dist[v]) {
	            dist[v] = dist[u] + weight;
	            prev[v] = u;
	            heap_change_key(pq, heap_search_data(pq, v), dist[v]);
	        }
	    }
	}

	int v = end;
	while (prev[v] != -1) {
	    int weight = dist[v] - dist[prev[v]];
	    insert_edge_start(path, prev[v], v, weight);
	    v = prev[v];
	}

	free(dist);
	free(prev);
	heap_clean(&pq);

	return path;
	}
