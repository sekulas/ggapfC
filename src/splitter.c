#include <stdlib.h>
#include <stdio.h>

#include "error_codes.h"
#include "graph.h"
#include "splitter.h"


void splitter(graph_t * graph) {
    
}

//returns info about node ( is it on the edge or not )
int is_on_the_edge(graph_t * graph, int node) {

    int k = 0;  //it's gona count how many connections a node have

    for(int i = 0; i < ADJ_LIST_COLS; i++)
        if(graph->edge[node][i].node != DEFAULT_NODE)
            k++;
        
    if( k < ADJ_LIST_COLS )
        return EDGE_NODE;
    
    return NOT_EDGE_NODE;

}