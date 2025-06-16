#include "graph.h"
#include "vertices.h"


typedef struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];    
}Graph;

Graph *graph_create(uint32_t vertices, bool undirected) {

    // Allocate memory
    Graph *G = (Graph*) malloc(sizeof(Graph));
    // if G = NULL return NULL
    if (G == NULL) { 
        return NULL; 
    }
    G->vertices = vertices; // Create pointer
    G->undirected = undirected;
    // Makes an initial array that is a mtrix of all zero's
    for (uint32_t i =0; i < VERTICES; i++) {
        G->visited[i] = false;
        for (uint32_t j = 0; j < VERTICES; j++) {
            G->matrix[i][j] = 0;
        }
    }
    return G;
}

void graph_delete(Graph **G) {

    if (*G ) {          //If G exits
        free(*G);      //Free memory
        *G = NULL;      //Set to Null
    }
    return;
}

uint32_t graph_vertices(Graph *G) {

    // Followed closely from asgn 3 
    if (G) {
        return G->vertices;
    }
    return 1;
}


// From a TA
bool b(int i, int j, int vertices) {
    return i >= 0 && j >= 0 && i < vertices && j < vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {

    // makes matrix[i][j] = matrix[j][i] and assigns a weight k to each matrix point
    if (G && b(i, j, G->vertices) && i != j) {
        G->matrix[i][j] = k;
        if (G->undirected) {
            G->matrix[i][j] = k;
        }
        return true;
    }
    return false;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {

    //i to j > 0 has an edge
    // if matrix[i][j] > 0
    //     has an edge
    // if i to j has no edge return 0

    if (G && b(i, j, G->vertices)) {
        return G->matrix[i][j] != 0;
    }
    return false;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {

    // if G exists and if i and j are in bounds return edge weight
    if (G && b(i, j, G->vertices)) {
        return G->matrix[i][j];
    }
    return 0;
}

bool graph_visited(Graph *G, uint32_t v) {

    // Checks if v was visited
    if (G && v < G->vertices) {
        return G->visited[v];
    }
    return false;
}

void graph_mark_visited(Graph *G, uint32_t v) {

    // marks the location visited
    if (G && v < G->vertices) {
        G->visited[v] = true;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {

    // marks graph unvisited if it has not been
    if (G && v < G->vertices) {
        G->visited[v] = false;
    }
    return;
}

void graph_print(Graph *G) {

    // Made something similar from asgn 3 and had help from jtennant
    for (uint32_t i = 0; i < G->vertices; i++) {
        printf("[");
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%2d ", G->matrix[i][j]);
        }
        printf("]\n");
    }
}
