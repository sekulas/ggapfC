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
    int current_node = end_node;                        //node we are currently in (part of the road)
    int following_node;                                 //node which is next to be visited (part of the road)
    int way;                                            //stores info about the direction road goes
    int e_node = starting_node;                         //just a ending node placeholder
    int mode = EDGE_CASE;                               //case with whicch we have to deal, there are two cases - normal and edge case when all of the nodes are on the top or right edge
    int node_to_cut;                                    //helps us storing the value of the node which is gonna to be cut basiccaly we are always cutting right or down node

    //it will store info from primary_prev about the fastest path, but quicker access
    int * road = malloc(sizeof(int) * graph->nodes);    //allocking memory for the array
    for(int i = 0; i < graph->nodes; i++)               //setting all nodes as not being part of the road
        road[i] = NOT_ON_THE_ROAD;                      
    road[current_node] = ON_THE_ROAD;                   //starting node is a part of a road
    road[e_node] = ON_THE_ROAD;                         //e_node is a part of the road
    while(current_node != e_node) {                     //adding rest nodes of the road
        road[current_node] = ON_THE_ROAD;
        current_node = primary_prev[current_node];
    }

    current_node = end_node;

    //looking if we have to deal with an edge case or normal case
    while( current_node != e_node ) {
        if( ((current_node % columns) == (columns - 1)) || ((current_node < columns)) ) {   //do nothing if on right or top edge
            fprintf(stderr, "no elo\n");
            current_node = primary_prev[current_node];
        }
        else {
            fprintf(stderr, "~ NORMAL CASE ~\n");
            mode = NORMAL_CASE;                                                             //if a node is not a part of the right or top edge it's a normal case
            break;
        }
    }

    current_node = end_node;

    if( mode == NORMAL_CASE ) {
/*      DO PRZEKMINIKI CZY NA STARCIE USOWAC WSZYSTKIE NA POCZATKU I NA KONCU 

        for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
            node_to_cut = graph->edge[current_node][i].node;
            if( (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE) ) { 
                graph->edge[current_node][i].node = DEFAULT_NODE;
                graph->edge[current_node][i].weight = DEFAULT_WEIGHT;
                fprintf(stderr, "START: Wyciumkano: %d\n", node_to_cut);
                for( int j = 0; j < ADJ_LIST_COLS; j++ )
                    if( graph->edge[node_to_cut][j].node == current_node ) {
                        graph->edge[node_to_cut][j].node = DEFAULT_NODE;
                        graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                }
            }
        }

        current_node = end_node;

*/
    
        while( current_node != e_node ) {
            
            following_node = primary_prev[current_node];

            //break lineas neearby starting position
            way = direction( rows, columns, current_node, following_node );

            if( way == UP ) {
                //looking for the right connection to break
                for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
                    node_to_cut = current_node + 1;            //setting current node to be cut
                    //looking if (this node of the graph need to be cut) && (if node to cut is not a part of the road) && (if there is node to cut)
                    if( (graph->edge[current_node][i].node == node_to_cut) && (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE) ) { 
                        graph->edge[current_node][i].node = DEFAULT_NODE;       //cutting node
                        graph->edge[current_node][i].weight = DEFAULT_WEIGHT;   //cutting node
                        fprintf(stderr, "UP: Wyciumkano: %d\n", node_to_cut);
                        for( int j = 0; j < ADJ_LIST_COLS; j++ )
                            if( graph->edge[node_to_cut][j].node == current_node ) {    //cutting node but from the second side
                                graph->edge[node_to_cut][j].node = DEFAULT_NODE;    
                                graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                        }
                    }
                }

                //deleting connection from previously deleted node
                for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
                    node_to_cut = following_node + 1;
                    if( (graph->edge[following_node][i].node == node_to_cut) && (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE) ) { 
                        graph->edge[following_node][i].node = DEFAULT_NODE;
                        graph->edge[following_node][i].weight = DEFAULT_WEIGHT;
                        for( int j = 0; j < ADJ_LIST_COLS; j++ )
                            if( graph->edge[node_to_cut][j].node == following_node ) {
                                graph->edge[node_to_cut][j].node = DEFAULT_NODE;
                                graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                            }
                    }
                }

            }
            else if( way == RIGHT ) {
                //looking for the down connection to break
                for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
                    node_to_cut = current_node + columns;
                    if( (graph->edge[current_node][i].node == node_to_cut) && (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE)) {
                        graph->edge[current_node][i].node = DEFAULT_NODE;
                        graph->edge[current_node][i].weight = DEFAULT_WEIGHT;
                        fprintf(stderr, "RIGHT: Wyciumkano: %d\n", node_to_cut);
                        for( int j = 0; j < ADJ_LIST_COLS; j++ )
                            if( graph->edge[node_to_cut][j].node == current_node ) {
                                graph->edge[node_to_cut][j].node = DEFAULT_NODE;
                                graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                            }
                    }
                }

                //deleting connection from previously deleted node
                for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
                    node_to_cut = following_node + columns;
                    if( (graph->edge[following_node][i].node == node_to_cut) && (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE)) {
                        graph->edge[following_node][i].node = DEFAULT_NODE;
                        graph->edge[following_node][i].weight = DEFAULT_WEIGHT;
                        for( int j = 0; j < ADJ_LIST_COLS; j++ )
                            if( graph->edge[node_to_cut][j].node == following_node ) {
                                graph->edge[node_to_cut][j].node = DEFAULT_NODE;
                                graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                            }
                    }
                }
                


            }
            else if( way == DOWN ) {
                //looking for the down connection to break
                for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
                    node_to_cut = current_node - 1;
                    if( (graph->edge[current_node][i].node == node_to_cut) && (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE) ) {
                        graph->edge[current_node][i].node = DEFAULT_NODE;
                        graph->edge[current_node][i].weight = DEFAULT_WEIGHT;
                        fprintf(stderr, "DOWN: Wyciumkano: %d\n", node_to_cut);
                        for( int j = 0; j < ADJ_LIST_COLS; j++ )
                            if( graph->edge[node_to_cut][j].node == current_node ) {
                                graph->edge[node_to_cut][j].node = DEFAULT_NODE;
                                graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                            }
                    }
                }

                //deleting connection from previously deleted node
                for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
                    node_to_cut = following_node - 1;
                    if( (graph->edge[following_node][i].node == node_to_cut) && (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE) ) {
                        graph->edge[following_node][i].node = DEFAULT_NODE;
                        graph->edge[following_node][i].weight = DEFAULT_WEIGHT;
                        for( int j = 0; j < ADJ_LIST_COLS; j++ )
                            if( graph->edge[node_to_cut][j].node == following_node ) {
                                graph->edge[node_to_cut][j].node = DEFAULT_NODE;
                                graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                            }
                    }
                }
                        
            }
            else if( way == LEFT ) {
                //looking for the down connection to break
                for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
                    node_to_cut = current_node - columns;
                    if( (graph->edge[current_node][i].node == node_to_cut) && (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE) ) {
                        graph->edge[current_node][i].node = DEFAULT_NODE;
                        graph->edge[current_node][i].weight = DEFAULT_WEIGHT;
                        fprintf(stderr, "LEFT: Wyciumkano: %d\n", node_to_cut);
                        for( int j = 0; j < ADJ_LIST_COLS; j++ )
                            if( graph->edge[node_to_cut][j].node == current_node ) {
                                graph->edge[node_to_cut][j].node = DEFAULT_NODE;
                                graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                            }
                    }
                }

                //deleting connection from previously deleted node
                for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
                    node_to_cut = following_node - columns;
                    if( (graph->edge[following_node][i].node == node_to_cut) && (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE) ) {
                        graph->edge[following_node][i].node = DEFAULT_NODE;
                        graph->edge[following_node][i].weight = DEFAULT_WEIGHT;
                        for( int j = 0; j < ADJ_LIST_COLS; j++ )
                            if( graph->edge[node_to_cut][j].node == following_node ) {
                                graph->edge[node_to_cut][j].node = DEFAULT_NODE;
                                graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                            }
                    }
                }
                        
            }
            
            current_node = primary_prev[current_node];
        }

    }
    else {
        while( current_node != e_node ) {
            fprintf(stderr, "~~~~~~~~~~~~~~~~~EDGE CASE ~~~~~~~~~~~~~~~~~~~~\n");
            following_node = primary_prev[current_node];

            way = direction( rows, columns, current_node, following_node );

            if( way == UP ) {
                //looking for the right connection to break
                for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
                    node_to_cut = current_node - 1;
                    if( (graph->edge[current_node][i].node == node_to_cut) && (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE) ) { 
                        graph->edge[current_node][i].node = DEFAULT_NODE;
                        graph->edge[current_node][i].weight = DEFAULT_WEIGHT;
                        fprintf(stderr, "UP: Wyciumkano: %d\n", node_to_cut);
                        for( int j = 0; j < ADJ_LIST_COLS; j++ )
                            if( graph->edge[node_to_cut][j].node == current_node ) {
                                graph->edge[node_to_cut][j].node = DEFAULT_NODE;
                                graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                            }
                    }
                }

                //deleting connection from previously deleted node
                for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
                    node_to_cut = following_node - 1;
                    if( (graph->edge[following_node][i].node == node_to_cut) && (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE) ) { 
                        graph->edge[following_node][i].node = DEFAULT_NODE;
                        graph->edge[following_node][i].weight = DEFAULT_WEIGHT;
                        fprintf(stderr, "UP: Wyciumkano: %d\n", node_to_cut);
                        for( int j = 0; j < ADJ_LIST_COLS; j++ )
                            if( graph->edge[node_to_cut][j].node == following_node ) {
                                graph->edge[node_to_cut][j].node = DEFAULT_NODE;
                                graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                            }
                    }
                }

            }
            else if( way == LEFT ) {
                //looking for the down connection to break
                for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
                    node_to_cut = current_node + columns;
                    if( (graph->edge[current_node][i].node == node_to_cut) && (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE) ) {
                        graph->edge[current_node][i].node = DEFAULT_NODE;
                        graph->edge[current_node][i].weight = DEFAULT_WEIGHT;
                        fprintf(stderr, "LEFT: Wyciumkano: %d\n", node_to_cut);
                        for( int j = 0; j < ADJ_LIST_COLS; j++ )
                            if( graph->edge[node_to_cut][j].node == current_node ) {
                                graph->edge[node_to_cut][j].node = DEFAULT_NODE;
                                graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                            }
                    }
                }

                //deleting connection from previously deleted node
                for( int i = 0; i < ADJ_LIST_COLS; i++ ) {
                    node_to_cut = following_node + columns;
                    if( (graph->edge[following_node][i].node == node_to_cut) && (road[node_to_cut] == NOT_ON_THE_ROAD) && (node_to_cut != DEFAULT_NODE) ) {
                        graph->edge[following_node][i].node = DEFAULT_NODE;
                        graph->edge[following_node][i].weight = DEFAULT_WEIGHT;
                        fprintf(stderr, "LEFT: Wyciumkano: %d\n", node_to_cut);
                        for( int j = 0; j < ADJ_LIST_COLS; j++ )
                            if( graph->edge[node_to_cut][j].node == following_node ) {
                                graph->edge[node_to_cut][j].node = DEFAULT_NODE;
                                graph->edge[node_to_cut][j].weight = DEFAULT_WEIGHT;
                            }
                    }
                }
                        
            }
        }

        current_node = primary_prev[current_node];
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