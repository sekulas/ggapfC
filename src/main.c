#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct elem { // do pliku graph.h
    double wage;
    int node;
} elem_t;

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

    FILE *in, *out;
    int nodes;
    elem_t **graph_arr;

    while ((opt = getopt (argc, argv, "h::s::x::y::n::b:e:r::f::t::")) != -1) {
        switch (opt) {
            case 'h':
                show_help(); 
                break;
            case 's':
                source_file = optarg;
                break;
            case 'x':
                columns = atoi(optarg);
                break;
            case 'y':
                rows = atoi(optarg);
                break;
            case 'n':
                subgraphs = atoi(optarg);
                break;
            case 'b':
                begin_node = atoi(optarg);
                break;
            case 'e':
                end_node = atoi(optarg);
                break;
            case 'r':
                result_file = optarg;
                break;
            case 'f':
                from_weight = atof(optarg);
                break;
            case 't':
                to_weight = atof(optarg);
                break;
            default:                  
                show_help(); // albo wypisz error
                exit (EXIT_FAILURE);
        }
    }

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
        graph_arr = generate_graph(rows, columns, from_weight, to_weight); //generuje graf spójny 

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
