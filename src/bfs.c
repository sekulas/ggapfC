#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "graph.h"
#include "queue.h"
#include "error_codes.h"
#include "bfs.h"
#include "splitter.h"
//bfs - returns 0 if graphs is connected, 1 if not
int bfs(graph_t * graph, int starting_node, int mode, char * primary_seen) {

        int connected_graph = CONNECTED_GRAPH;  //variable which will store info about our graph being connected or not

        //declaring queue for bfs
        queue_ptr_t q = NULL;

        //declaring an array which will store info about seen nodes
        char * seen = malloc(sizeof(char) * graph->nodes);      //allocking memory for array seen
        if(seen == NULL) {
            fprintf(stderr, "bfs(): 'seen' allocation failed");
            exit(SEEN_FAILED_ALLOC);
        }

        memset(seen, UNSEEN_NODE, graph->nodes); //setting every node as unseen
        q = queue_add( q, starting_node );       //adding starting node to queue

        //bfs algorithm
        while( !queue_empty(q) ) {
            
            seen[queue_top(q)] = SEEN_NODE;             //mark current node as seen
            jump_into( graph, queue_top(q), seen, q);   //look for neighbours
            q = queue_pop(q);                           //pop current node from queue

        }

        connected_graph = is_graph_connected( graph, seen );
        if( connected_graph ) {
            
            //if we are in a SPLIT_MODE we need a seen table for future operations
            fprintf(stderr, "CLONING PRIMARY_SEEN BEEP                              ****\n");
            if(mode == SPLIT_MODE)
                for(int i = 0; i < graph->nodes; i++)
                    primary_seen[i] = seen[i];  
        
        }

        free(seen);
        return connected_graph;

        
}


//function which jumps into a node (necessary for bfs)
void jump_into(graph_t * graph, int starting_node, char * seen, queue_ptr_t q) {

    int adjacent_node;  //it's gona store value of adjacent node

    for(int i = 0; i < ADJ_LIST_COLS; i++) {

        adjacent_node = graph->edge[starting_node][i].node; 

        if(adjacent_node != DEFAULT_NODE)          //if neighbour exist
            if(seen[adjacent_node] == UNSEEN_NODE) { //if neighbour has not been visited
                q = queue_add(q, adjacent_node);   //add it to queue
                seen[adjacent_node] = SEEN_NODE;
            }
    }

}

//returns 0 if graph is connected or 1 if graph is not connected
//actually it's looking if in array seen exist any unseen node if yes then
//graph is not connected otherwise it's connected
int is_graph_connected(graph_t * graph, char * seen) {

    //looking if graphs is connected
    for(int i = 0; i < graph->nodes; i++)      
        if( seen[i] == UNSEEN_NODE ) 
            return NOT_CONNECTED_GRAPH;

    return CONNECTED_GRAPH;

}