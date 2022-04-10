#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "graph.h"
#include "queue.h"
#include "error_codes.h"
#include "bfs.h"

//bfs - returns 0 if graphs is connected, 1 if not
int bfs(graph_t * graph, int starting_node) {

        //declaring queue for bfs
        queue_ptr_t q = NULL;

        //declaring an array which will store info about seen nodes
        char * seen = malloc(graph->nodes);      //allocking memory for array seen
        if(seen == NULL) {
            fprintf(stderr, "bfs(): 'seen' allocation failed");
            exit(SEEN_FAILED_ALLOC);
        }

        memset(seen, UNSEEN_NODE, graph->nodes); //setting every node as unseen
        seen[starting_node] = SEEN_NODE;         //setting starting node as seen
        q = queue_add( q, starting_node );       //adding starting node to queue

        //bfs algorithm
        while( !queue_empty(q) ) {
            
            seen[queue_top(q)] = SEEN_NODE;             //mark current node as seen
            jump_into( graph, queue_top(q), seen, q);   //look for neighbours
            q = queue_pop(q);                           //pop current node from queue

        }

        return is_graph_connected( graph, seen );
        
}


//function which jumps into a node (necessary for bfs)
void jump_into(graph_t * graph, int starting_node, char * seen, queue_ptr_t q) {

    int adjective_node; //it's gona store value of adjective node

    for(int i = 0; i < ADJ_LIST_COLS; i++) {

        adjective_node = graph->edge[starting_node][i].node; 

        if(adjective_node != DEFAULT_NODE)          //if neighbour exist
            if(seen[adjective_node] == UNSEEN_NODE) //if neighbour has not been visited
                q = queue_add(q, adjective_node);   //add it to queue
    }

}

//returns 0 if graph is connected or 1 if graph is not connected
//actually it's looking if in array seen exist any unseen node if yes then
//graph is not connected otherwise it's connected
int is_graph_connected(graph_t * graph, char * seen) {

    for(int i = 0; i < graph->nodes; i++) {
        
        if( seen[i] == UNSEEN_NODE ) { 
            free(seen);
            return NOT_CONNECTED_GRAPH;
        }

    }

    free(seen);
    return CONNECTED_GRAPH;

}