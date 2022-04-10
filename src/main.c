/* wersja-szkic niekompilowalna */
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int flags[10]; //Tablica przechowujaca dane o tym czy flaga sie pojawila

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
            case 'h':
                show_help();
                flags[H] = 1; 
                break;
            case 's':
                source_file = optarg;
                //printf("source_file: %s\n", optarg);
                flags[S] = 1;
                break;
            case 'x':
                columns = atoi(optarg);
                //printf("columns: %d\n", columns);
                flags[X] = 1;
                break;
            case 'y':
                rows = atoi(optarg);
                //printf("rows: %d\n", rows);
                flags[Y] = 1;
                break;
            case 'n':
                subgraphs = atoi(optarg);
                //printf("subgraphs: %d\n", subgraphs);
                flags[N] = 1;
                break;
            case 'b':
                begin_node = atoi(optarg);
                //printf("begin_node: %d\n", begin_node);
                flags[B] = 1;
                break;
            case 'e':
                end_node = atoi(optarg);
                //printf("end_node: %d\n", end_node);
                flags[E] = 1;
                break;
            case 'r':
                result_file = optarg;
                //printf("result_file: %s\n", optarg);
                flags[R] = 1;
                break;
            case 'f':
                from_weight = atof(optarg);
                //printf("from_weight: %g\n", from_weight);
                flags[F] = 1;
                break;
            case 't':
                to_weight = atof(optarg);
                //printf("to_weight: %g\n", to_weight);
                flags[T] = 1;
                break;
            default:
                fprintf(stderr, "Invalid usage of flag or used flag does not exist.\nSmall help for you:\n\n");                  
                show_help(); // albo wypisz error
                exit (EXIT_FAILURE);
        }
    }

    nodes = columns * rows;

    //Nie podano wymaganych flag
    if(!flags[5] || !flags[6]) {
        fprintf(stderr, "Flags -b -e are necessary!\n");
        show_help();
        return 1;
    }
    //Niepoprawne wagi
    if( ( flags[8] || flags[9] ) && from_weight > to_weight ) {
        fprintf(stderr, "Wrong wage range! Your input:\n from:%g to:%g \n", from_weight, to_weight);
        show_help();
        return 1;
    }
    //Niepoprawne subgraphy
    if( flags[4] && ( subgraphs < 1 || subgraphs > (nodes / 2) ) ) {
        fprintf(stderr, "There is no option to divide this graph to %d subgraphs!\n", subgraphs);
        show_help();
        return 1;
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
		exit( EXIT_FAILURE );
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
  
    // the functions that generate the graph terminate the program when an error is encountered
    // so no need to check if graph is NULL 

    if(bfs(graph, 0) == 0) {                                        // sprawdzanie spojnosci grafu - zwraca 0 jezeli jest spojny 1 jesli jest nie spojny
        printf("Wczytany graf jest spojny.\n");
    } else
        printf("Wczytany graf jest niespojny zatem podzial na podgrafy nie nastapi\n");

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
    //fclose(in);
    //fclose(out);

    // !!!sprawdzic wycieki valgrindem!!!

    return 0;
}
