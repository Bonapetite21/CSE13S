#include "path.h"


typedef struct Path {
    Stack *vertices; 
    uint32_t length; 
} Path;

// From Eric's office hours
Path *path_create(void) {
    // Allocate memory
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

void path_delete(Path **p) {
    // p is not equal to pointer to p
    if (p && *p) { 
        stack_delete(&((*p)->vertices)); 
        free(*p); // free's memory
        *p = NULL; // set to null
    }
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t lastvertex;
    // Checks if stack is empty 
    bool is_empty = !(stack_peek(p->vertices, &lastvertex)); 
    // If no vertcies on the path set distance from origin to vertex
    if (is_empty) {
        p->length = graph_edge_weight(G, 0, v);
    } else { // else set distance from last vertex to origin
        p->length += graph_edge_weight(G, lastvertex, v);
    }
    return stack_push(p->vertices, v);
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t current_vertex;
    bool pop = stack_pop(p->vertices, &current_vertex);
    uint32_t lastvertex;
    bool peek = stack_peek(p->vertices, &lastvertex);

    // Decreases the length to the last vertex to origin if this condion is satisfied and passes vertex through the pointer
    if (pop && peek) {
        p->length -= graph_edge_weight(G, lastvertex, current_vertex);
        *v = current_vertex; 
    }
    return pop && peek;
}

uint32_t path_vertices(Path *p) {
    // size of the stack vertices
    return stack_size(p->vertices); 
}

uint32_t path_length(Path *p) {
    // Length of the path
    return p->length; 
}

void path_copy(Path *dst, Path *src) {
    // check if destination exists and then copies it to the stack
    if (src && dst) { 
        stack_copy(dst->vertices, src->vertices);
        dst->length = src->length; 
    }
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    // prints for testing purposes of the path
    fprintf(outfile, "Path length: %d\n", p->length); 
    fprintf(outfile, "Path: ");
    stack_print(p->vertices, outfile, cities); 
}
