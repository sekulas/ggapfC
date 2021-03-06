#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "reader.h"
#include "graph.h"
#include "error_codes.h"

// returns pointer to graph structure on success end error code to shell in other case
graph_t * read_from_file(char * filename) {
    int rows;       // rows number in graph
    int columns;    // columns number in graph
    int tmp;        // temp variable for reading characters
    int node;       // node read from file
    double weight;  // weight read from file
    int i;          // index of current node in adj list
    graph_t * graph;    // pointer to graph structure

    FILE * in = fopen(filename, "r");

    if(in == NULL) {
        fprintf(stderr, "read_from_file(): can not open source file!\n");
        exit(READER_CANNOT_OPEN_SRC);
    }

    // parsing first line, looking for rows and columns number
    if(fscanf(in, "%d %d", &rows, &columns) != 2) {
        fprintf(stderr, "read_from_file(): wrong data format!\n");
        exit(READER_WRONG_FORMAT);
    }
    
    graph = init_graph(rows, columns);

    // skipping additional parameters for compatibility with java version
    // compatibility with both LF and CRLF break line sequences
    while((tmp = fgetc(in)) != EOF) {
        if(tmp == CR) tmp = fgetc(in);
        if(tmp == LF) break;    // skipping until reaching a new line
    }

    i = 0;
    while((tmp = fscanf(in, "%d:%lf", &node, &weight)) != EOF) {
        if(tmp != 2) {
            fprintf(stderr, "read_from_file(): wrong data format!\n");
            exit(READER_WRONG_FORMAT);
        }

        // validate and add values to graph
        add_edge(graph, i, node, weight);

        // skiping spaces between nodes
        // important for last pair in line
        while(isspace(tmp = fgetc(in))) {
            if(tmp == CR) tmp = fgetc(in);
            if(tmp == LF) ++i;    // next node in adj list
        }
        ungetc(tmp, in);    // first character that is not a space
    }

    fclose(in);
    return graph;
}