#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include "dijkstra.h"

/* USAGE:
    cc src/tester.c src/reader.c src/dijkstra.c src/priority_queue.c src/graph.c -lm
    ./a.out <mode> <params..>
    ./a.out r filename begin_node end_node                  - reads and shows graph from file and finds shortest path
    ./a.out w rows cols from_weight to_weight filename      - generates graph with given params
*/

int main(int argc, char ** argv) {
    if(argc < 2) return 1;
    
    graph_t * graph = NULL;
    FILE * out = NULL;
    int begin_node, end_node;

    if(argv[1][0] == 'r') graph = read_from_file(argv[2]);
    if(argv[1][0] == 'w') graph = generator(atoi(argv[2]), atoi(argv[3]), atof(argv[4]), atof(argv[5]));

    if(argc > 5) out = fopen(argv[6], "w");
    if(out == NULL) out = stdout;

    show_graph(graph, out);

    if(argv[1][0] == 'r' && argc > 3)
        dijkstra(graph, atoi(argv[3]), atoi(argv[4]), 1);
    
    free_graph(graph);
    return 0;
}