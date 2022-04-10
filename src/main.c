/* wersja-szkic niekompilowalna */
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_codes.h"
#include "reader.h"
#include "const.h"
#include "graph.h"
#include "bfs.h"

void show_help() {
    fprintf(stderr, "!!!HELP!!!\n");
    return;
}

int main (int argc, char **argv) {
    int opt;
    char *source_file = NULL;
    char *result_file = NULL;
    int columns = 5;
    int rows = 5;
    int subgraphs = 1;
    int begin_node = -1;
    int end_node = -1;
    double from_weight = 1.0;
    double to_weight = 10.0;
    double path_length;
    int flags; //variable cointaining info about used flags (bitoperations)

    //FILE *in, *out; zamykamy to w konkretnych modulach
    int nodes;
    graph_t * graph;

    //HELP
    if( argc == 2 && (!strcmp("-?", argv[1]) || !strcmp("-help", argv[1]) || !strcmp("--help", argv[1]))) {
        show_help();
        return 0;
    }

    /*
        https://azrael.digipen.edu/~mmead/www/Courses/CS180/getopt.html
        getopt quick guide:
        ":" - taki znak po danej fladze znaczy, że dana flaga wymaga podania argumentu
              jeżeli funkcja nie dostanie argumentu w wywala znak "?" - czyli wchodzi w default
        brak czegokolwiek po literce znaczy, że nie potrzebuje ona zadnego argumentu - dana flaga aktywuje jakas funkcje
    */

    while ((opt = getopt (argc, argv, "hs:x:y:n:b:e:r:f:t:")) != -1) {
        switch (opt) {
            case HELP_FLAG:
                show_help();
                flags += HELP_FLAG_BIT;
                break;
            case SOURCE_FILE_FLAG:
                source_file = optarg;
                //printf("source_file: %s\n", optarg);
                flags += SOURCE_FILE_FLAG_BIT;
                break;
            case COLUMNS_FLAG:
                columns = atoi(optarg);
                //printf("columns: %d\n", columns);
                flags += COLUMNS_FLAG_BIT;
                break;
            case ROWS_FLAG:
                rows = atoi(optarg);
                //printf("rows: %d\n", rows);
                flags += ROWS_FLAG_BIT;
                break;
            case SUBGRAPHS_FLAG:
                subgraphs = atoi(optarg);
                //printf("subgraphs: %d\n", subgraphs);
                flags += SUBGRAPHS_FLAG_BIT;
                break;
            case BEGIN_NODE_FLAG:
                begin_node = atoi(optarg);
                //printf("begin_node: %d\n", begin_node);
                flags += BEGIN_NODE_FLAG_BIT;
                break;
            case END_NODE_FLAG:
                end_node = atoi(optarg);
                //printf("end_node: %d\n", end_node);
                flags += END_NODE_FLAG_BIT;
                break;
            case RESULT_FILE_FLAG:
                result_file = optarg;
                //printf("result_file: %s\n", optarg);
                flags += RESULT_FILE_FLAG_BIT;
                break;
            case FROM_WEIGHT_FLAG:
                from_weight = atof(optarg);
                //printf("from_weight: %g\n", from_weight);
                flags += FROM_WEIGHT_FLAG_BIT;
                break;
            case TO_WEIGHT_FLAG:
                to_weight = atof(optarg);
                //printf("to_weight: %g\n", to_weight);
                flags += TO_WEIGHT_FLAG_BIT;
                break;
            default:
                fprintf(stderr, "Invalid usage of flag or used flag does not exist.\nSmall help for you:\n\n");                  
                show_help(); // albo wypisz error
                exit (INVALID_FLAG);
        }
    }

    nodes = columns * rows;

    //Nie podano wymaganych flag
    if(!(flags & BEGIN_NODE_FLAG_BIT) || !(flags & END_NODE_FLAG_BIT)) {
        fprintf(stderr, "Flags -b -e are necessary!\n");
        show_help();
        exit(LACK_OF_B_OR_E_FLAG);
    }
    //Niepoprawne wagi
    if( ((flags & FROM_WEIGHT_FLAG_BIT) || (flags & TO_WEIGHT_FLAG_BIT)) && from_weight > to_weight ) {
        fprintf(stderr, "Wrong wage range! Your input:\n from:%g to:%g \n", from_weight, to_weight);
        show_help();
        exit(WRONG_WAGES);
    }
    //Niepoprawne subgraphy
    if( (flags & SUBGRAPHS_FLAG_BIT) && ( subgraphs < 1 || subgraphs > (nodes / 2) ) ) {
        fprintf(stderr, "There is no option to divide this graph to %d subgraphs!\n", subgraphs);
        show_help();
        exit(CANNOT_DIVIDE);
    }

    /*
        Funkcja lapie non option arguments
    */
	if( optind < argc ) {
		fprintf( stderr, "\nBad parameters!\n" );
		for( ; optind < argc; optind++ )
			fprintf( stderr, "\t\"%s\"\n", argv[optind] );
		fprintf( stderr, "\n" );
		show_help();
		exit( BAD_PARAMETERS );
	}

    // !!!walidacja parametrów!!!
    // .... sprawdzenie ich sensownosci - zakresy itp

    /* malocowanie listy sasiedztwa - do pliku graph.c
    nodes = columns * rows;
    elem_t **graph = malloc(sizeof(graph) * nodes); // tablica n x 4
    
    for(int i = 0; i < nodes; i++) 
        graph[i] = malloc(sizeof(graph[i]) * 4);
    */

    // if filename is given as parameter
    if(source_file != NULL)
        graph = read_from_file(source_file);
    else
        graph = generate_graph(rows, columns, from_weight, to_weight);
    // the functions that generate the graph terminate the program when an error is encountered
    // so no need to check if graph is NULL    

    if(bfs(graph, 0) == 0) {                                        // sprawdzanie spojnosci grafu - zwraca 0 jezeli jest spojny 1 jesli jest nie spojny
        printf("Graph is connected!\n");
        if(subgraphs > 1) {
            printf("Graph will be divided to %d subgraphs\n", subgraphs);
                splitter(graph, rows, columns, subgraphs);                          // dzielenie grafu 
        } else 
            printf("Graph cannot be divided.\n");
    } else
        printf("Graph is not connected - it will not be divided to subgraphs.\n");
        

    //!!!Sprawdzaj czy begin_node i end_node sa tym samym wtedy 0!!!
    path_length = dijkstra(graph, rows, columns, begin_node, end_node);         // odleglosci miedzy begin_node i end_node
    
    //jezeli plik wyjsciowy jest podany
    if(result_file != NULL) {
        out = fopen(result_file, "w");
        if( out == NULL ) {
            fprintf(stderr, "Cannot open result file!\n");
            exit(CANNOT_ACCESS_OUT);
        }
    } else // w innym wypadku wypisz na standardowe wyjscie
        out = stdout; 
    
    writer(graph, out);

    /*
        jeżeli podany source_file
            sprawdź spójność - bfs
            podziel na n podgrafów (jeżeli się da)
            znajdz sciezke - dijkstra
            zapisz do pliku
        w przeciwnym wypadku
            wygeneruj graf o podanych parametrach
            podziel graf
            znajdz sciezke
            zapisz do pliku
    */

    for(int i = 0; i < nodes; i++) 
        free(graph[i]);
    free(graph);
    fclose(in);
    fclose(out);

    // !!!sprawdzic wycieki valgrindem!!!

    return 0;
}
