#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "writer.h"
#include "error_codes.h"
#include "graph.h"

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
        fprintf(stderr, "save_to_file(): can not create result file!\n");
        exit(WRITER_CANNOT_CREATE_FILE);
    }

    // print to file
    show_graph(graph, out);

    // close file
    fclose(out);
}

// prints the graph to the selected file
void save_to_graphml(graph_t * graph, char * filename) {
    // when filename is NULL print on stdout
    if(filename == NULL) {
        fprintf(stderr, "save_to_file(): filename NULL!\n");
        return;
    }

    // add graphml extension
    char * filename_graphml = malloc(sizeof(char) * (strlen(filename) + 10));
    filename_graphml = strcpy(filename_graphml, filename);
    filename_graphml = strcat(filename_graphml, ".graphml");

    // try open file for writing
    FILE * out = NULL;
    out = fopen(filename_graphml, "w");

    if(out == NULL) {
        fprintf(stderr, "save_to_file(): can not create result file!\n");
        exit(WRITER_CANNOT_CREATE_FILE);
    }

    // print to file
    show_graphml(graph, out);

    // close file
    fclose(out);
    free(filename_graphml);

}