#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "error_codes.h"

// prints the graph to the selected file
// when filename is NULL prints to stdout
void save_to_file(graph_t * graph, char * filename) {
    // when filename is NULL print on stdout
    if(filename == NULL) {
        fprintf(stderr, "save_to_file(): filename NULL, print on stdout!\n");
        show_graph(graph, stdout);
        return;
    }

    // try open file for writing
    FILE * out = NULL;
    out = fopen(filename, "w");

    if(out == NULL) {
        fprintf(stderr, "save_to_file(): can not open source file!\n");
        exit(WRITER_CANNOT_CREATE_FILE);
    }

    // print to file
    show_graph(graph, out);

    // close file
    fclose(out);
}