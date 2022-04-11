#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "reader.h"
#include "dijkstra.h"
#include "splitter.h"
#include "bfs.h"

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
    int * to_split = NULL;
    char * seen = NULL;
    int starting_node;
    int end_node;
    int * prev;

    // read from file and find shortest path
    if(argv[1][0] == 'r') {
        graph = read_from_file(argv[2]);
        if(argc > 3) dijkstra(graph, atoi(argv[3]), atoi(argv[4]), 1, to_split, NOT_SPLIT_MODE);
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

                while(1) {
                    starting_node = rand() % graph->nodes;      //looking for a starting
                    end_node = rand() % graph->nodes;           //looking for a end node

                    if(starting_node != end_node)               //is not starting node same as end node
                        if( is_on_the_edge(graph, starting_node) && is_on_the_edge(graph, end_node) ); //are they on the edges
                            bfs(graph, starting_node, SPLIT_MODE, seen);  //let's see if they're connected

                    if(seen[end_node] == SEEN_NODE) {                       //if they're connected
                        dijkstra(graph, atoi(argv[3]), atoi(argv[4]), 1, prev, SPLIT_MODE); //look for the shortest path
                        splitter(graph, prev);                              //split
                        free(prev);                                         //free memory from dijkstra prev
                        break;
                    }
                    else {
                        free(seen);                            //free memory from the bfs about connections
                        continue;                              //look one more time for the nodes
                    }
                }
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