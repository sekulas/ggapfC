#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_codes.h"
#include "const.h"
#include "graph.h"
#include "reader.h"
#include "writer.h"
#include "bfs.h"
#include "dijkstra.h"
#include "splitter.h"

void show_help();

int main (int argc, char **argv) {
    int     opt;
    char    *source_file    = NULL;
    char    *result_file    = NULL;
    int     columns         = 5;
    int     rows            = 5;
    int     subgraphs       = 1;
    int     begin_node      = -1;
    int     end_node        = -1;
    double  from_weight     = 1.0;
    double  to_weight       = 10.0;
    double  path_length;
    int     flags = 0;      //variable cointaining info about used flags (bitoperations)

    int nodes;
    graph_t *graph;

    // help detection
    if( argc == 1 || (argc == 2 && (!strcmp("-?", argv[1]) || !strcmp("-help", argv[1]) || !strcmp("--help", argv[1])))) {
        show_help();
        return 0;
    }

    while ((opt = getopt (argc, argv, "hs:x:y:n:b:e:r:f:t:")) != -1) {
        switch (opt) {
            case HELP_FLAG:
                show_help();
                flags |= HELP_FLAG_BIT;
                break;
            case SOURCE_FILE_FLAG:
                source_file = optarg;
                //printf("source_file: %s\n", optarg);
                flags |= SOURCE_FILE_FLAG_BIT;
                break;
            case COLUMNS_FLAG:
                columns = atoi(optarg);
                //printf("columns: %d\n", columns);
                flags |= COLUMNS_FLAG_BIT;
                break;
            case ROWS_FLAG:
                rows = atoi(optarg);
                //printf("rows: %d\n", rows);
                flags |= ROWS_FLAG_BIT;
                break;
            case SUBGRAPHS_FLAG:
                subgraphs = atoi(optarg);
                //printf("subgraphs: %d\n", subgraphs);
                flags |= SUBGRAPHS_FLAG_BIT;
                break;
            case BEGIN_NODE_FLAG:
                begin_node = atoi(optarg);
                //printf("begin_node: %d\n", begin_node);
                flags |= BEGIN_NODE_FLAG_BIT;
                break;
            case END_NODE_FLAG:
                end_node = atoi(optarg);
                //printf("end_node: %d\n", end_node);
                flags |= END_NODE_FLAG_BIT;
                break;
            case RESULT_FILE_FLAG:
                result_file = optarg;
                //printf("result_file: %s\n", optarg);
                flags |= RESULT_FILE_FLAG_BIT;
                break;
            case FROM_WEIGHT_FLAG:
                from_weight = atof(optarg);
                //printf("from_weight: %g\n", from_weight);
                flags |= FROM_WEIGHT_FLAG_BIT;
                break;
            case TO_WEIGHT_FLAG:
                to_weight = atof(optarg);
                //printf("to_weight: %g\n", to_weight);
                flags |= TO_WEIGHT_FLAG_BIT;
                break;
            default:
                fprintf(stderr, "Invalid usage of flag or used flag does not exist.\nSmall help for you:\n\n");                  
                show_help();
                exit (INVALID_FLAG);
        }
    }

    nodes = columns * rows;

    // lack of required flags
    if(!(flags & BEGIN_NODE_FLAG_BIT) || !(flags & END_NODE_FLAG_BIT)) {
        fprintf(stderr, "main(): Flags -b -e are necessary!\n");
        show_help();
        exit(LACK_OF_B_OR_E_FLAG);
    }
    // wrong weights
    if( ((flags & FROM_WEIGHT_FLAG_BIT) || (flags & TO_WEIGHT_FLAG_BIT)) && from_weight > to_weight ) {
        fprintf(stderr, "main(): Wrong weight range! Your input:\n from:%g to:%g \n", from_weight, to_weight);
        show_help();
        exit(WRONG_WAGES);
    }
    // wrong subraphs number
    if( (flags & SUBGRAPHS_FLAG_BIT) && ( subgraphs < 1 || subgraphs > (nodes / 2) ) ) {
        fprintf(stderr, "main(): There is no option to divide this graph to %d subgraphs!\n", subgraphs);
        show_help();
        exit(CANNOT_DIVIDE);
    }

    // non option arguments
	if( optind < argc ) {
		fprintf( stderr, "\nmain(): Bad parameters!\n" );
		for( ; optind < argc; optind++ )
			fprintf( stderr, "\t\"%s\"\n", argv[optind] );
		fprintf( stderr, "\n" );
		show_help();
		exit( BAD_PARAMETERS );
	}

    // if filename is given as parameter
    if(source_file != NULL)
        graph = read_from_file(source_file);
    else
        graph = generator(rows, columns, from_weight, to_weight);
        // the functions that generate the graph terminate the program when an error is encountered
        // so no need to check if graph is NULL    

    // checking if graph is connected
    if(bfs(graph, 0, NOT_SPLIT_MODE, NULL) == CONNECTED_GRAPH) {
        printf("Graph is connected!\n");
        if(subgraphs > 1) {
            printf("Graph will be divided to %d subgraphs\n", subgraphs);
            // splitting graph
            split_graph(graph, subgraphs);
        } else 
            printf("Graph will not be divided.\n");
    } else
        printf("Graph is not connected - it will not be divided to subgraphs.\n");
        
    // find shortest path between begin_node and end_node
    path_length = dijkstra(graph, begin_node, end_node, SHOW_BACKTRACE, NULL, NOT_SPLIT_MODE);
    
    // print graph to result_file
    // if result_file is NULL print on stdout
    save_to_file(graph, result_file);

    // additional feature - prints graph in graphml file format
    // you can visualise it here: https://graphonline.ru/en/
    if(graph->nodes <= 1000000) // for bigger graphs graphml file is too large
        save_to_graphml(graph, result_file);

    free_graph(graph);

    return 0;
}

void show_help() {
    printf(
        "Ggapf works in two modes:\n"
        "\t1. On given graph:\n\n"
        "\t ./ggapf -s source_file -n subgraphs -b begin_node -e end_node -r result_file\n\n"
        "\t  Tries to open [source_file], when graph is connected splits is to [subgraphs] subgraphs\n"
        "\t  Finds the shortest path using Dijkstras algorithm from [begin_node] to [end_node]\n"
        "\t  Saves graph in [result_file] if it is specified or prints on stdout\n\n"
        "\t2. Generates new graph:\n\n"
        "\t ./ggapf -x rows -y columns -f from_weight -t to_weight -n subgraphs -b begin_node -e end_node -r result_file\n\n"
        "\t  Generates a [rows] x [columns] size undirected graph with random weighted edges in range <[from_weight];[to_weight]>\n"
        "\t  Splits it to [subgraphs] subgraphs (when specified)\n"
        "\t  Finds the shortest path using Dijkstras algorithm from [begin_node] to [end_node]\n"
        "\t  Saves graph in [result_file] if it is specified or prints on stdout\n\n"
        "\t2. Examples:\n"
        "\t./ggapf -x 100 -y 200 -f 0 -t 10 -n 1 -b 0 -e 37 -r tmp\n"
        "\t  - generates 100x200 graph with weights from range [0;10], finds shortest path between nodes 0 and 37, saves graph into tmp\n"
        "\t./ggapf -s tmp -n 3 -b 0 -e 39 -r tmp\n"
        "\t  - reads graph from tmp, if it is connected splits it to 3 subgraphs, finds shortest path between nodes 0 and 39, saves graph into tmp1"
    );
}
