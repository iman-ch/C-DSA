/**
 * -------------------------------------
 * @file  heap.c
 * Assignment 9
 * -------------------------------------
 * @author
 *
 * @version 2024-02-22
 *
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

HEAP *new_heap(int capacity) {
    HEAP *heap = (HEAP *)malloc(sizeof(HEAP));
    if (!heap) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    heap->size = 0;
    heap->capacity = capacity;
    heap->hda = (HEAPDATA *)malloc(capacity * sizeof(HEAPDATA));
    if (!heap->hda) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    return heap;
}

void heap_insert(HEAP *heap, HEAPDATA data) {
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
    while (i > 0 && data.key < heap->hda[(i - 1) / 2].key) {
        heap->hda[i] = heap->hda[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->hda[i] = data;
    return;
}

HEAPDATA heap_find_min(HEAP *heap) {
    return heap->hda[0];
}

HEAPDATA heap_extract_min(HEAP *heap) {
    HEAPDATA min_data = heap->hda[0];
    heap->size--;
    heap->hda[0] = heap->hda[heap->size];

    int i = 0;
    while (2 * i + 1 < heap->size) {
        int left_child = 2 * i + 1;
        int right_child = 2 * i + 2;
        int min_child = (right_child < heap->size && heap->hda[right_child].key < heap->hda[left_child].key) ? right_child : left_child;

        if (heap->hda[min_child].key < heap->hda[i].key) {
            HEAPDATA temp = heap->hda[i];
            heap->hda[i] = heap->hda[min_child];
            heap->hda[min_child] = temp;
            i = min_child;
        } else {
            break;
        }
    }

    if (heap->size > 4 && heap->size <= heap->capacity / 4) {
        heap->capacity /= 2;
        heap->hda = (HEAPDATA *)realloc(heap->hda, heap->capacity * sizeof(HEAPDATA));
        if (!heap->hda) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }

    return min_data;
}

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key) {
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

int heap_search_data(HEAP *heap, VALUETYPE val) {
    for (int i = 0; i < heap->size; i++) {
        if (heap->hda[i].value == val) {
            return i;
        }
    }
    return -1;
}

void heap_clean(HEAP **heapp) {
    free((*heapp)->hda);
    free(*heapp);
    *heapp = NULL;
}

