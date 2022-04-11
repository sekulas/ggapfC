#include <stdlib.h>
#include <stdio.h>

#include "error_codes.h"
#include "graph.h"
#include "splitter.h"
#include "bfs.h"


void splitter(graph_t * graph, int * primary_prev, char * primary_seen, int starting_node, int end_node) {
    
    int rows = graph->rows;
    int columns = graph->columns;

    for(int i = 0; i < rows * columns; i++)
        fprintf(stderr, "prev[%d] = %d\n", i, primary_prev[i]);

    //our primary_prev table contains ancestors, so we should start from the end
    //reversing start and end
    int current_node = end_node;
    int following_node;
    int e_node = starting_node;

    while( current_node != end_node ) {

    }



    exit(0);

}

int direction( int rows, int columns, int current_node, int following_node ) {



    if( following_node == ( current_node - columns ) )
        return UP;
    
    if( following_node == ( current_node + 1 ) )
        return RIGHT;
    
    if( following_node == ( current_node + columns ) )
        return DOWN;
    
    if( following_node == ( current_node - 1 ) )
        return LEFT;


}

//returns info about node ( is it on the edge or not )
int is_on_the_edge(graph_t * graph, int node) {

    int k = 0;  //it's gona count how many connections a node have

    for(int i = 0; i < ADJ_LIST_COLS; i++)
        if(graph->edge[node][i].node != DEFAULT_NODE)
            k++;
        
    fprintf(stderr, "k: %d\n", k);

    if( k != ADJ_LIST_COLS ) {
        fprintf(stderr, "edge_node\n");
        return EDGE_NODE;
    }
    
    return NOT_EDGE_NODE;

}