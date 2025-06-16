#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

#include "graph.h"
#include "vertices.h"
#include "path.h"

void help(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "  Traveling Salesman Problem using DFS.\n"
        "\n"
        "USAGE\n"
        "  %s [-u] [-v] [-h] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -u             Use undirected graph.\n"
        "  -v             Enable verbose printing.\n"
        "  -h             Program usage and help.\n"
        "  -i infile      Input containing graph (default: stdin)\n"
        "  -o outfile     Output of computed path (default: stdout)\n",
        exec); 
}

int number_of_recursions = 0;
// Had help from jtennant
void dfs (Graph *G, uint32_t v, Path *curr , Path * shortest, char * cities [] , FILE * outfile, bool verbose) {
    number_of_recursions++;
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);
    uint32_t trash;     // Getting rid of uneeded variables

    // Print statement for debugging
    // printf(" - - - CALL: %d - - - \n", i);
    // printf("currently searching from %s\n", cities[v]);
    // printf("current path:\n");
    // path_print(curr, outfile, cities);

    // checks if vertex has been visited once and reachable
    if (path_vertices(curr) == graph_vertices(G) && graph_has_edge(G, v, START_VERTEX)) {
        // printf("ham path found!\n");     // Print statement for debugging
        path_push_vertex(curr, START_VERTEX, G);
        // if this hamiltonain path is shorter than any previous hamiltonian paths
        if (path_length(curr) < path_length(shortest) || !path_length(shortest)) {
            // printf("shortest ham path!\n");      // Print statement for debugging
            // if verbose printing enabled then print path
            if (verbose == true) {
                path_print(curr, outfile, cities);
            }
            // update shortest path
            path_copy(shortest, curr);
        }
        path_pop_vertex(curr, &trash, G);
        path_pop_vertex(curr, &trash, G);
        graph_mark_unvisited(G, v);
        return;
    }
    for (uint32_t u = 0; u < graph_vertices(G); u++) {
        // printf("considering path from %s to %s ...\n", cities[v], cities[u]);        // Print statement for debugging
        bool not_visited = graph_visited(G, u) == false;
        bool not_the_same = v != u;
        bool edge_exists = graph_has_edge(G, v, u);
        bool still_shorter = path_length(curr) + graph_edge_weight(G, v, u) < path_length(shortest);
        bool not_found = path_length(shortest) == 0;
        // printf("%d %d %d %d %d\n", not_visited, not_the_same, edge_exists, still_shorter, not_found);        // Print statement for debugging
        if ((not_visited && not_the_same && edge_exists) && (still_shorter || not_found)) {
            // printf("going from %s to %s ...\n", cities[v], cities[u]);           // Print statement for debugging
            dfs(G, u, curr, shortest, cities, outfile, verbose);
        }
    }
    // printf("all paths from %s exausted. going back ...\n", cities[v]);       // Print statement for debugging
    graph_mark_unvisited(G, v);
    path_pop_vertex(curr, &trash, G);
    // printf("path after pop:\n");         // Print statement for debugging
    // path_print(curr, outfile, cities);           // Print statement for debugging
    return;
}


// First attempt at DFS
//  void dfs (Graph *G, uint32_t v, Path *curr , Path * shortest, char * cities [] , FILE * outfile) {
//     // graph_mark_visited(v);
//     graph_visited(G, v);
//     // for (w = 0 ... G->vertices) {
//     //     if (graph_has_edge(v, w) && graph_mark_unvisited(w)) {
//     //         DFS(G, w);
//     //     }
//     for (uint32_t i = 0; i < VERTICES; i++) { 
//         if (graph_has_edge(G, v, i) && graph_mark_unvisited(G, i)) {
//             path_push_vertex(curr, i, G);
//             dfs(G, i, curr, shortest, cities, outfile);
//             path_pop_vertex(curr, &i, G);
//         }
//     }
//     // graph_mark_unvisited(v);
//     graph_mark_unvisited(G, v);
//     // }

//     uint32_t shortest_path = path_length(shortest_path);
//     uint32_t curr_path_length = path_length(curr_path_length);


//     if (curr_path_length <= shortest_path) {
//         stack_copy(Stack shortest_path, current stack);
//     }
// }


#define OPTIONS "huvi:o:"
#define BLOCK 4096

int main(int argc, char **argv) {

    bool undirected = false;
    bool verbose = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int opt;

    // creating switch statements for calling specified flags for the assignment 
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'h': 
                help(argv[0]);
                fclose(infile);
                fclose(outfile);
                return 0;

            case 'u': 
                undirected = true;
                break;

            case 'v':
                verbose = true;
                break;

            case 'i':
                infile = fopen(optarg, "r");
                break;

            case 'o':
                outfile = fopen(optarg, "w");
                break;

            default:
                help(argv[0]);
                fclose(infile);
                fclose(outfile);
                return 1;
        }
    }

    // total number of vertices
    int tot_vertices;
    int in = fscanf(infile, "%d\n", &tot_vertices); // Scan first line of infile
    // Checking if this is valid
    if (in != 1 || tot_vertices < 2 || tot_vertices > 26) {
        printf("Invalid vertices\n");
        return 1;
    }

    // storing all the cities
    char buffer[BLOCK];
    char *cities[tot_vertices]; 
    // iterates through and stores cities in an array
    for (int i = 0; i < tot_vertices; i++) {
        fgets(buffer, BLOCK, infile);
        cities[i] = strdup(buffer);
        // trimming last charachter \n of city name
        cities[i][strlen(cities[i]) - 1] = '\0';
    }

    // making the graph
    Graph *graph = graph_create(tot_vertices, undirected);

    // Gives all edges of cities
    int i, j, k;
    // iterates throgh the edges and checks for proper format
    while ((in = fscanf(infile, "%d %d %d\n", &i, &j, &k)) != -1) {
        if (in == 3) { // must have 3 numbers for scnaf to be successful
            graph_add_edge(graph, i, j, k);
        } else { // else not formatted propperly
            printf("edge not formatted properly\n");
            return 1;
        }
    }

    // graph_print(graph);      // Print statement for debugging

    // creates path fro current and shortest path
    Path *curr = path_create();
    Path *shortest =path_create();

    // Runs dfs
    dfs(graph, START_VERTEX, curr, shortest, cities, outfile, verbose);

    // Check for no hamiltonian path fopund
    if (path_length(shortest) != 0) {
        path_print(shortest, outfile, cities);
    }
    fprintf(outfile, "Total recursuve calls: %d\n", number_of_recursions);

    // Free's all memory and closes files
    graph_delete(&graph);
    path_delete(&curr);
    path_delete(&shortest);
    fclose(infile);
    fclose(outfile);
    return 0;
}


// I/O notes from Eugene

//     char buffer[BLOCK];
    
//     int i, j, k;
//     int c;
//     FILE *infile = fopen("test.txt", "r");
    
//     if (infile == NULL) {
//         fprintf(stderr, "failed to open test.txt");
//         return 1;
//     }

//     while (c = fscanf(infile, "%d\n", &i) != EOF) {
//         if (c != 3) {
//             printf("malformed line\n");
//             break;
//         }
//         printf("i = %d\n", i);
//     }
// }

// typedef enum {

// }

// #define BLOCK 4096

// int main(void) {
//     char buffer[BLOCK];
//     int i, j, k;
//     int c;

//     FILE *infile = fopen("test.txt", "r");
//     if (infile == NULL) {
//         fprintf(stderr, "failed to open test.txt");
//         return 1;
//     }

//     while (c = fscanf(infile, "%d %d %d\n", &i, &j, &k) != EOF) {
//         if (c != 3) {
//             printf("malformed line\n");
//             break;
//         }
//         printf("i = %d\n", i);
//         printf("i = %d\n", j);
//         printf("i = %d\n", k);
//     }

//     FILE *outfile = fopen("out.txt", "w");
//     if (outfile == NULL) {
//         fprintf(stderr, "failed to open out.txt");
//         return 1;
//     }

//     while (c = fscanf(infile, "%d %d %d\n", &i, &j, &k) != EOF) {
//         if (c != 3) {
//             printf("malformed line\n");
//             break;
//         }
//         printf(outfile, "i = %d\n", i);
//         printf(outfile, "i = %d\n", j);
//         printf(outfile, "i = %d\n", k);
//     }


//     while (c = fscanf(stdin, "%d %d %d\n", &i, &j, &k) != EOF) {
//         if (c != 3) {
//             printf("malformed line\n");
//             break;
//         }
//         printf("i = %d\n", i);
//         printf("i = %d\n", j);
//         printf("i = %d\n", k);
//     }

//     while (fgets(buffer(buffer, BLOCK, stdin))) {
//         fputs(buffer, stdout);
//     }
//     return 0;
// }

