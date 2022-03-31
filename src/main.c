#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "const.h"
#include "graph.h"

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

    FILE *in, *out;
    int nodes;
    pair_t **graph_arr;

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
                fprintf(stderr, "NIEPOPRAWIE UZYTA FLAGA LUB FLAGA NIE ISTNIEJE\nTutaj masz podrecznego helpa:\n\n");                  
                show_help(); // albo wypisz error
                exit (EXIT_FAILURE);
        }
    }

    nodes = columns * rows;

    //Nie podano wymaganych flag
    if(!flags[5] || !flags[6]) {
        fprintf(stderr, "NIE PODANO WYMAGANYCH FLAG -b i -e\n");
        show_help();
        return 1;
    }
    //Niepoprawne wagi
    if( ( flags[8] || flags[9] ) && from_weight > to_weight ) {
        fprintf(stderr, "NIEPRAWIDLOWY ZAKRES WAG\n");
        show_help();
        return 1;
    }
    //Niepoprawne subgraphy
    if( flags[4] && ( subgraphs < 1 || subgraphs > (nodes / 2) ) ) {
        fprintf(stderr, "NIE DA SIE PODZIELIC GRAFU NA TYLE SUBGRAPHOW\n");
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
    elem_t **graph_arr = malloc(sizeof(graph_arr) * nodes); // tablica n x 4
    
    for(int i = 0; i < nodes; i++) 
        graph_arr[i] = malloc(sizeof(graph_arr[i]) * 4);
    */

    // jeżeli podany jakiś plik wejściowy
    if(source_file != NULL) {
        in = fopen(source_file, "r");
        if(in == NULL) {
            fprintf(stderr, "Nie udalo sie otworzyc pliku wejsciowego!\n");
            return EXIT_FAILURE;
        }
        // podejmij probe odczytu
        graph_arr = read_from_file(source_file); //reader
    } else // jeżeli nie podano pliku wejściowego
        graph_arr = generate_graph(rows, columns, from_weight, to_weight); // generuje graf spójny 

    if(graph_arr == NULL) {
        fprintf(stderr, "Fatal error: nie udalo sie stworzyc grafu!\n");
        return EXIT_FAILURE;
    }
    
    if(bfs(graph_arr, rows, columns) == 0) {                                        // sprawdzanie spojnosci grafu - zwraca 0 jezeli jest spojny 1 jesli jest nie spojny
        printf("Wczytany graf jest spojny.\n");
        if(subgraphs > 1) {
            printf("Graf zostanie podzielony na %d podgrafow\n", subgraphs);
            splitter(graph_arr, rows, columns, subgraphs);                          // dzielenie grafu 
        } else 
            printf("Graf nie bedzie dzielony.\n");
    } else
        printf("Wczytany graf jest niespojny zatem podzial na podgrafy nie nastapi\n");
        

    //!!!Sprawdzaj czy begin_node i end_node sa tym samym wtedy 0!!!
    path_length = dijkstra(graph_arr, rows, columns, begin_node, end_node);         // odleglosci miedzy begin_node i end_node
    
    //jezeli plik wyjsciowy jest podany
    if(result_file != NULL) {
        out = fopen(result_file, "w");
        if( out == NULL ) {
            fprintf(stderr, "Nie udalo sie otworzyc pliku wyjsciowego!\n");
            return EXIT_FAILURE;
        }
    } else // w innym wypadku wypisz na standardowe wyjscie
        out = stdout; 
    
    writer(graph_arr, out);

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
        free(graph_arr[i]);
    free(graph_arr);
    fclose(in);
    fclose(out);

    // !!!sprawdzic wycieki valgrindem!!!

    return 0;
}
