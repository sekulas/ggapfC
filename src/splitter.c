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
    int way;
    int e_node = starting_node;
    int mode = EDGE_CASE;

    //we are on the right edge or top edge case
    while( current_node != e_node ) {
        if( ((current_node % columns) == (columns - 1)) || ((current_node < columns)) ) {
            fprintf(stderr, "no elo\n");
            current_node = primary_prev[current_node];
        }
        else {
            fprintf(stderr, "~ NORMAL CASE ~\n");
            mode = NORMAL_CASE;
            break;
        }
    }



    if( mode == NORMAL_CASE ) {

        for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
            if( graph->edge[current_node][i].node != primary_prev[current_node] ) {
                fprintf(stderr, "START: Wyciumkano: %d\n", graph->edge[current_node][i].node );
                graph->edge[current_node][i].node = DEFAULT_NODE;
                graph->edge[current_node][i].weight = DEFAULT_WEIGHT;
            }
        } 
    
        while( current_node != e_node ) {
            
            following_node = primary_prev[current_node];

            //break lineas neearby starting position


            way = direction( rows, columns, current_node, following_node );

            if( way == UP ) {
                //looking for the right connection to break
                for( int i = 0; i < ADJ_LIST_COLS; i++ )
                    if( graph->edge[current_node][i].node == current_node + 1 ) { 
                        graph->edge[current_node][i].node = DEFAULT_NODE;
                        graph->edge[current_node][i].weight = DEFAULT_WEIGHT;
                        fprintf(stderr, "UP: Wyciumkano: %d\n", current_node + 1);
                    }

            }
            else if( way == RIGHT ) {
                //looking for the down connection to break
                for( int i = 0; i < ADJ_LIST_COLS; i++ )
                    if( graph->edge[current_node][i].node == current_node + columns ) {
                        graph->edge[current_node][i].node = DEFAULT_NODE;
                        graph->edge[current_node][i].weight = DEFAULT_WEIGHT;
                        fprintf(stderr, "RIGHT: Wyciumkano: %d\n", current_node + columns);
                    }


            }
            else if( way == DOWN ) {
                //looking for the down connection to break
                for( int i = 0; i < ADJ_LIST_COLS; i++ )
                    if( graph->edge[current_node][i].node == current_node - 1) {
                        graph->edge[current_node][i].node = DEFAULT_NODE;
                        graph->edge[current_node][i].weight = DEFAULT_WEIGHT;
                        fprintf(stderr, "DOWN: Wyciumkano: %d\n", current_node - 1);
                    }
                        
            }
            else if( way == LEFT ) {
                //looking for the down connection to break
                for( int i = 0; i < ADJ_LIST_COLS; i++ )
                    if( graph->edge[current_node][i].node == current_node - columns ) {
                        graph->edge[current_node][i].node = DEFAULT_NODE;
                        graph->edge[current_node][i].weight = DEFAULT_WEIGHT;
                        fprintf(stderr, "LEFT: Wyciumkano: %d\n", current_node - columns);
                    }
                        
            }
            
            current_node = primary_prev[current_node];
        }
    }
    else {
        while( current_node != e_node ) {
            fprintf(stderr, "~~~~~~~~~~~~~~~~~EDGE CASE ~~~~~~~~~~~~~~~~~~~~\n");
        }
    }

}

//direction guesser
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