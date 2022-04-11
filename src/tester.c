#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include "dijkstra.h"
#include "splitter.h"

/* USAGE:
    cc src/tester.c src/reader.c src/dijkstra.c src/priority_queue.c src/graph.c -lm
    ./a.out <mode> <params..>
    ./a.out r filename begin_node end_node                  - reads and shows graph from file and finds shortest path
    ./a.out w rows cols from_weight to_weight filename      - generates graph with given params
    ./a.out c source destination.graphml                   
*/

void show_help() {
    printf(
        "USAGE:\n"
        "\t./a.out <mode> <params..>\n"
        "\t./a.out r filename begin_node end_node                  - reads and shows graph from file and finds shortest path\n"
        "\t./a.out w rows cols from_weight to_weight filename      - generates graph with given params\n"
        "\t./a.out c source destination.graphml                    - converts our file format to graphml file\n"
        "\t./a.out s source destination.graphml to_split           - converts file and splits it"
    );
}

int main(int argc, char ** argv) {
    if(argc < 2) {
        show_help();
        return 1;
    }
    
    graph_t * graph = NULL;
    FILE * out = NULL;
    int begin_node, end_node;
    int * to_split;

    // read from file and find shortest path
    if(argv[1][0] == 'r') {
        graph = read_from_file(argv[2]);
        if(argc > 3) dijkstra(graph, atoi(argv[3]), atoi(argv[4]), 1, to_split, BASIC_DIJKSTRA);
        else printf("give me more parameters\n");
    }

    // generate and save
    if(argv[1][0] == 'w') {
        graph = generator(atoi(argv[2]), atoi(argv[3]), atof(argv[4]), atof(argv[5]));
        if(argc > 5) {
            out = fopen(argv[6], "w");
            show_graph(graph, out);
            printf("saved to %s\n", argv[6]);
            fclose(out);
        } else {
            printf("not saved\n");
        }
    }

    // convert to graphml format
    if(argv[1][0] == 'c') {
        graph = read_from_file(argv[2]);
        if(argc > 2) {
            out = fopen(argv[3], "w");
            show_graphml(graph, out);
            printf("%s converted to %s\n",argv[2], argv[3]);
            fclose(out);
        } else {
            printf("give me destination filename\n");
        }
    }

    if(argv[1][0] == 's') {
       graph = read_from_file(argv[2]);
        if(argc > 2) {
            out = fopen(argv[3], "w");

            for(int i = 0; i < atoi(argv[4]); i++) {
                //TUTAJ ZABAWA DIJKSTRA AZ ZNAJDZIESZ GITGUT SCIEZKE
                splitter(graph);
            }

            show_graphml(graph, out);
            printf("%s converted to %s\n",argv[2], argv[3]);
            fclose(out);
        } else {
            printf("give me destination filename\n");
        }
    }


    // add bfs here or something

    free_graph(graph);

    return 0;
}