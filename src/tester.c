#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graph.h"
#include "reader.h"
#include "writer.h"
#include "dijkstra.h"
#include "splitter.h"
#include "bfs.h"

/* USAGE:
    cc src/tester.c src/reader.c src/writer.c src/dijkstra.c src/priority_queue.c src/graph.c src/bfs.c src/splitter.c src/queue.c -o tester -lm
    ./a.out <mode> <params..>
    ./a.out r filename begin_node end_node                  - reads and shows graph from file and finds shortest path
    ./a.out w rows cols from_weight to_weight filename      - generates graph with given params
    ./a.out c source destination.graphml                   
    ./a.out s source destination.graphml split_fragments              
*/

void show_help() {
    printf(
        "USAGE:\n"
        "\t./a.out <mode> <params..>\n"
        "\t./a.out r filename begin_node end_node                  - reads and shows graph from file and finds shortest path\n"
        "\t./a.out w rows cols from_weight to_weight filename      - generates graph with given params\n"
        "\t./a.out c source destination.graphml                    - converts our file format to graphml file\n"
        "\t./a.out s source destination.graphml to_split           - converts file and splits it\n"
    );
}

int main(int argc, char ** argv) {
    if(argc < 2) {
        show_help();
        return 1;
    }

    srand(time(NULL));
    
    graph_t * graph = NULL;
    FILE * out = NULL;
    int begin_node, end_node;
    char * primary_seen = NULL;                 //seen table which will be gathering informations from bfs seen
    int * primary_prev = NULL;                  //prev table which will be gathering informations from dijkstra
    int starting_node;


    // read from file and find shortest path
    if(argv[1][0] == 'r') {
        graph = read_from_file(argv[2]);
        if(argc > 3) dijkstra(graph, atoi(argv[3]), atoi(argv[4]), 1, primary_prev, NOT_SPLIT_MODE);
        else printf("give me more parameters\n");
    }

    // generate and save
    if(argv[1][0] == 'w') {
        graph = generator(atoi(argv[2]), atoi(argv[3]), atof(argv[4]), atof(argv[5]));
        if(argc > 5) {
            save_to_file(graph, argv[6]);
            printf("saved to %s\n", argv[6]);
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

    // split graph
    if(argv[1][0] == 's') {
       graph = read_from_file(argv[2]);

        fprintf(stderr, "ZACZYNAMY ZABAWE!\n");

        primary_seen = malloc(sizeof(char) * graph->nodes);                 //seen table which will be gathering informations from bfs seen
        primary_prev = malloc(sizeof(int) * graph->nodes);    //prev table which will be gathering informations from dijkstra
        
        if(argc > 2) {
            out = fopen(argv[3], "w");

            for(int i = 1; i < atoi(argv[4]); i++) {
                
                fprintf(stderr, "%d SPLIT\n", i);

                while(1) {
                    
                    memset(primary_seen, UNSEEN_NODE, graph->nodes);        //setting every node as unseen

                    for( int j = 0; j < graph->nodes; j++)      //change value of the whole primary array to DEFAULT_NODE
                        primary_prev[j] = DEFAULT_NODE;            

                    fprintf(stderr, "set_up\n");

                    starting_node = rand() % graph->nodes;      //looking for a starting node 

                    while( is_on_the_edge( graph, starting_node )  == NOT_EDGE_NODE ) {
                        starting_node = rand() % graph->nodes;      //looking for a starting node on the edge
                        fprintf(stderr, "starting node\n");
                    }

                    bfs(graph, starting_node, SPLIT_MODE, primary_seen);  //let's see if they're connected

                    //looking for end node through bfs table
                    while(1) {

                        end_node = rand() % graph->nodes;

                        if( is_on_the_edge( graph, end_node ) && primary_seen[end_node] == SEEN_NODE  ) {
                            fprintf(stderr, "end node\n");
                            break;
                        }

                        fprintf(stderr, "looking for end node\n");

                    }

                    if(primary_seen[end_node] == SEEN_NODE) {                                  //if they're connected
                        fprintf(stderr, "~~ jest koneksja!                          ######\n");
                        dijkstra(graph, starting_node, end_node, 1, primary_prev, SPLIT_MODE); //look for the shortest path
                        splitter(graph, primary_prev, primary_seen, starting_node, end_node);                              //split
                        break;
                    }
                    else  
                        continue;                              //look one more time for the nodes   
                    
                }
            }
            free(primary_seen);                                         //free memory from seen (bfs)
            free(primary_prev);                                         //free memory from dijkstra prev

            show_graphml(graph, out);
            printf("%s converted to %s\n",argv[2], argv[3]);
            fclose(out);
        } else
            printf("give me destination filename\n");

    }
    // add bfs here or something

    free_graph(graph);

    return 0;
}