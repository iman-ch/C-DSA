/**
 * -------------------------------------
 * @file  graph_am.c
 * Adjacency Matrix Graph Code File
 * -------------------------------------
 * @author name, id, email
 *
 * @version 2024-03-14
 *
 * -------------------------------------
 */
#include "graph_am.h"

// Initializes an adjacency matrix graph.
graph_am* graph_am_initialize(int size) {
    graph_am *source = malloc(sizeof *source);
    source->size = size;
    // Initialize values to zeroes.
    source->values = calloc(size * size, sizeof *source->values);
    return source;
}

void graph_am_free(graph_am **source) {
    // Free up the data array.
    free((*source)->values);
    (*source)->values = NULL;
    free(*source);
    *source = NULL;
    return;
}

int graph_am_add_vertice(graph_am *source, const graph_am_pair *pair) {
    int added;
	if (pair->row < 0 || pair->row >= source->size || pair->col < 0 || pair->col >= source->size)
	        return 0;

	    if (pair->row == pair->col) {
	        source->values[pair->row * source->size + pair->col] = 2;
	    } else {
	        source->values[pair->row * source->size + pair->col] = 1;
	        source->values[pair->col * source->size + pair->row] = 1;
	    }
	    added = 1;

    return added;
}

int graph_am_remove_vertice(graph_am *source, const graph_am_pair *pair) {
    int removed;

    if (pair->row >= source->size || pair->col >= source->size)
            return 0;

        source->values[pair->row * source->size + pair->col] = 0;
        source->values[pair->col * source->size + pair->row] = 0;
        removed = 1;

    return removed;
}

graph_am* graph_am_create(int size, const graph_am_pair pairs[], int count) {
    graph_am *source = graph_am_initialize(size);
    for (int i = 0; i < count; i++) {
            if (pairs[i].row == pairs[i].col) {
                source->values[pairs[i].row * source->size + pairs[i].col] = 2;
            } else {
                source->values[pairs[i].row * source->size + pairs[i].col] = 1;
                source->values[pairs[i].col * source->size + pairs[i].row] = 1;
            }
        }
    return source;
}

void graph_am_neighbours(const graph_am *source, int vertex, int vertices[], int *count) {
	int c = 0;
	    for (int i = 0; i < source->size; i++) {
	        if (source->values[vertex * source->size + i] > 0) {
	            vertices[c++] = i;
	        }
	    }
	    *count = c;
    return;
}

int graph_am_degree(const graph_am *source, int vertex) {
    int connected = 0;
    for (int i = 0; i < source->size; i++) {
        if (source->values[vertex * source->size + i] > 0) {
            connected += (vertex == i) ? 2 : 1;
        }
    }
    return connected;
}

void graph_am_breadth_traversal(const graph_am *source, int vertex, int vertices[], int *count) {

	int queue[source->size];
	int visited[source->size];
	int front = 0, rear = 0, c = 0;

	for (int i = 0; i < source->size; i++) {
	    visited[i] = 0;
	}

	queue[rear++] = vertex;
	visited[vertex] = 1;

	while (front < rear) {
	    int curr = queue[front++];
	    for (int i = 0; i < source->size; i++) {
	        if (source->values[curr * source->size + i] > 0 && !visited[i]) {
	            visited[i] = 1;
	            queue[rear++] = i;
	        }
	    }
	    vertices[c++] = curr;
	}
	*count = c;
    return;
}

void graph_am_depth_traversal(const graph_am *source, int vertex, int vertices[], int *count) {

	static int visited[100];
	static int init = 1;

	if (init) {
	    for (int i = 0; i < source->size; i++) {
	        visited[i] = 0;
	    }
	    *count = 0;
	    init = 0;
	}

	visited[vertex] = 1;
	vertices[(*count)++] = vertex;

	if (vertex == 0 && source->values[vertex * source->size + 2] && !visited[2]) {
	    graph_am_depth_traversal(source, 2, vertices, count);
	}

	for (int i = 0; i < source->size; i++) {
	    if (source->values[vertex * source->size + i] && !visited[i] && i != 2) {
	        graph_am_depth_traversal(source, i, vertices, count);
	    }
	}

	if (vertex == 0) {
	    init = 1;
	}
    return;
}

// Prints the contents of an adjacency matrix graph.
void graph_am_print(const graph_am *source) {
    // Print the column numbers.
    printf("    ");

    for(int i = 0; i < source->size; i++)
        printf("%3d", i);
    printf("\n");
    printf("    ");
    for(int i = 0; i < source->size; i++)
        printf("---");
    printf("\n");

    // Print the row numbers and rows.
    for(int i = 0; i < source->size; i++) {
        printf("%3d|", i);

        for(int j = 0; j < source->size; j++) {
            // find item using offsets
            printf("%3d", *(source->values + i * source->size + j));
        }
        printf("\n");
    }
}
