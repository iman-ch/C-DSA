/*
 * your program signature
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "heap.h"

int cmp(KEYTYPE a, KEYTYPE b) {
  int r = 0;
  if (a < b) r = -1;
  else if (a > b) r = 1;
  return r;
}

HEAP *new_heap(int capacity)
{
  HEAP *hp = (HEAP*) malloc(sizeof(HEAP));
  if (hp == NULL) return NULL;
  hp->hda = (HEAPDATA *) malloc(sizeof(HEAPDATA) * capacity);
  if ( hp->hda == NULL) { free(hp); return NULL; };
  hp->capacity = capacity;
  hp->size = 0;
  return hp;
}

// you may add this function to be used other functions.
int heapify_up(HEAPDATA *hda, int index) {
// your code
}

// you may add this function to be used other functions.
int heapify_down(HEAPDATA *hda, int n, int index) {
// your code
}

void heap_insert(HEAP *heap, HEAPDATA new_node) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->hda = (HEAPDATA *)realloc(heap->hda, heap->capacity * sizeof(HEAPDATA));
        if (!heap->hda) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }

    int i = heap->size;
    heap->size++;

    while (i > 0 && new_node.key < heap->hda[(i - 1) / 2].key) {
        heap->hda[i] = heap->hda[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    heap->hda[i] = new_node;
}

HEAPDATA heap_find_min(HEAP *heap)
{
    return heap->hda[0];
}

HEAPDATA heap_extract_min(HEAP *heap)
{
    HEAPDATA min_data = heap->hda[0];
    heap->size--;
    heap->hda[0] = heap->hda[heap->size];

    int i = 0;
    while (2 * i + 1 < heap->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int min = (right < heap->size && heap->hda[right].key < heap->hda[left].key) ? right : left;

        if (heap->hda[min].key < heap->hda[i].key) {
            HEAPDATA temp = heap->hda[i];
            heap->hda[i] = heap->hda[min];
            heap->hda[min] = temp;
            i = min;
        } 
        
        else break;
    }

    if (heap->size > 4 && heap->size <= heap->capacity / 4) {
        heap->capacity /= 2;
        heap->hda = (HEAPDATA *)realloc(heap->hda, heap->capacity * sizeof(HEAPDATA));
        if (!heap->hda) {
            min_data.key = -1; 
            return min_data;
        }
    }

    return min_data;
}

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key)
{
    int i = index;
    heap->hda[i].key = new_key;

    while (i > 0 && heap->hda[i].key < heap->hda[(i - 1) / 2].key) {
        HEAPDATA temp = heap->hda[i];
        heap->hda[i] = heap->hda[(i - 1) / 2];
        heap->hda[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }

    return i;
}

int heap_search_data(HEAP *heap, VALUETYPE data) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->hda[i].value == data) {
            return i;
        }
    }
    return -1;
}

void heap_clean(HEAP **heapp) {
  if (heapp) {
    HEAP *heap = *heapp;
    if (heap->capacity > 0) {
      heap->capacity = 0;
      heap->size = 0;
      free(heap->hda);
      free(heap);
    }
    *heapp = NULL;
  }
}