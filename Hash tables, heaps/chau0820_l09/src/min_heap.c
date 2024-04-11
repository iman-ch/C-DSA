/**
 * -------------------------------------
 * @file  min_heap.c
 * Minimum Heap Source Code File
 * -------------------------------------
 * @author Iman Chaudhry, id, email
 *
 * @version 2024-03-11
 *
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "min_heap.h"

#define STRING_SIZE 80

// local functions

/**
 * Swaps two data values.
 *
 * @param a pointer to data.
 * @param b pointer to data.
 */
static void heap_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

/**
 * Moves the last value in source until it is in its correct location
 * in source.
 *
 * @param source - pointer to a heap
 */
static void heapify_up(min_heap *source) {

	int index = source->count - 1; //
	    while (index > 0) {
	        int parentIndex = (index - 1) / 2;
	        if (source->values[index] < source->values[parentIndex]) {
	            heap_swap(&source->values[index], &source->values[parentIndex]);
	            index = parentIndex;
	        } else {
	            break;
	        }
	    }
}

/**
 * Moves a value down source to its correct position.
 *
 * @param source - pointer to a heap
 */
static void heapify_down(min_heap *source) {
	int i = 0;
    int smallerChild;
    int left, right;

    while (i < source->count) {

        smallerChild = i;
        left = 2 * i + 1;
        right = 2 * i + 2;

        if (left < source->count && source->values[left] < source->values[smallerChild]) {
            smallerChild = left;
        }

        if (right < source->count && source->values[right] < source->values[smallerChild]) {
            smallerChild = right;
        }

        if (smallerChild != i) {
            heap_swap(&source->values[i], &source->values[smallerChild]);
            i = smallerChild;
        } 
        
        else break;
    }
}

// Public minimum heap functions

min_heap* min_heap_initialize(int capacity) {
    min_heap *source = malloc(sizeof *source);
    source->values = malloc(capacity * sizeof *source->values);
    source->capacity = capacity;
    source->count = 0;
    return source;
}

void min_heap_free(min_heap **source) {
	if (source != NULL && *source != NULL) {
	        free((*source)->values);
	        (*source)->values = NULL;
	        free(*source);
	        *source = NULL;
	} 
    return;
}

void min_heap_heapify(min_heap *source, int *keys, int count) {

    for(int i = 0; i < count; i++) {
        min_heap_insert(source, keys[i]);
    }
    return;
}

int min_heap_empty(const min_heap *source) {
    return (source->count == 0);
}

int min_heap_full(const min_heap *source) {
    return (source->count == source->capacity);
}

int min_heap_count(const min_heap *source) {
    return (source->count);
}

void min_heap_insert(min_heap *source, const int value) {
    // Add new value to end of the heap.
    source->values[source->count] = value;
    source->count++;
    // Fix the heap.
    heapify_up(source);
    return;
}

int min_heap_peek(const min_heap *source) {
    return (source->values[0]);
}

int min_heap_remove(min_heap *source) {
    int value = source->values[0];
    source->count--;

    if(source->count > 0) {
        // Move last value to top of heap.
        source->values[0] = source->values[source->count];
        // Fix the heap.
        heapify_down(source);
    }
    return value;
}

int min_heap_valid(const min_heap *source) {
	for (int i = 0; i < source->count / 2; i++) {
	    int left = 2 * i + 1;
	    int right = 2 * i + 2;

	    if (left < source->count && source->values[i] > source->values[left]) {
	        return 0;
	    }

	    if (right < source->count && source->values[i] > source->values[right]) {
	        return 0;
	    }
	}

	return 1;
}

int min_heap_replace(min_heap *source, int replacement) {
    int value = source->values[0];
    source->values[0] = replacement;
    heapify_down(source);
    return value;
}

void heap_sort(int *values, int count) {
    min_heap *heap = min_heap_initialize(count);
	    min_heap_heapify(heap, values, count);

	    for (int i = 0; i < count; i++) {
	        values[i] = min_heap_remove(heap);
	    }

	    min_heap_free(&heap);
}

// for testing
void min_heap_print(const min_heap *source) {
    printf("{");

    for(int i = 0; i < source->count; i++) {
        printf("%d, ", source->values[i]);
    }
    printf("}\n");
    return;
}
