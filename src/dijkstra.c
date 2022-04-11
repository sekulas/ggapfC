#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "error_codes.h"
#include "graph.h"
#include "priority_queue.h"
#include "reader.h"
#include "dijkstra.h"
#include "splitter.h"

// for tests only
void print_distances_arr(double * arr, int n) {
    for(int i = 0; i < n; i++)
        printf("%d: %f\n", i, arr[i]);
}
void print_prev_arr(int * arr, int n) {
    for(int i = 0; i < n; i++)
        printf("%d: %d\n", i, arr[i]);
}


// shows the course of the shortest path
void backtrace(double * distance, int * prev, int begin, int end) {
    int current_vertex;
    int prev_vertex;
    int i = 0;
    double weight;

    // show shortest path or info that there is no shortest path
    if(distance[end] >= FLT_MAX) {
        printf("Shortest path = INFINITY\nThere is no path between given vertices\n");
        return;
    } else 
        printf("Shortest path = %g\n", distance[end]);

    // show vertices thorugh shortest path leads by
    // backtracing by prev array
    current_vertex = end;
    while(current_vertex != begin) {
        printf("%d <- ", current_vertex);
        current_vertex = prev[current_vertex];
    }
    printf("%d\n\n", current_vertex);

    // show individual weights between vertices on shortest path
    // backtracing by prev array
    printf("Weights of individual edges:\n");
    current_vertex = end;
    while(current_vertex != begin) {
        prev_vertex = prev[current_vertex];
        weight = distance[current_vertex] - distance[prev_vertex];

        printf("%5d <- %-5d  =  %g\n", current_vertex, prev_vertex, weight);
        current_vertex = prev_vertex;
        i++;
    }

    // additional info
    printf("\nThe shortest path leads through %d vertices\n\n", i);
}

// finds shortest path betweent given vertices
// returns shortest path lenght or DBL_MAX when there is no path between given vertices
// if show_backtrace != 0, the course of the shortest path will be presented
double dijkstra(graph_t * graph, int begin, int end, int show_backtrace, int * to_split, int mode) {
    
    if(begin < 0 || begin >= graph->nodes || end < 0 || end >= graph->nodes) {
        fprintf(stderr, "dijkstra(): given indexes out of range!\n");
        exit(DIJKSTRA_OUT_OF_RANGE);
    }

    if(graph == NULL) {
        fprintf(stderr, "dijkstra(): given graph is NULL!\n");
        exit(DIJKSTRA_NULL_GRAPH);
    }
    
    int i;          // iterator
    double result;  // shortest path between given vertices

    pair_t current;     // the vertex from which the paths are examined
    pair_t examined;    // the vertex to which examined path leads
    double new_distance;    // potential new distance between current and examined

    double * distance = malloc(sizeof(double) * graph->nodes);  // currently known shortest paths lengths
    int * seen = malloc(sizeof(int) * graph->nodes);            // for marking examined vertices
    int * prev = malloc(sizeof(int) * graph->nodes);            // vertex through which the shortest path leads

    pq_t * pq = init_pq();      // priority queue used in algorithm

    if(distance == NULL || seen == NULL || prev == NULL) {
        fprintf(stderr, "dijkstra(): allocation failed!\n");
        exit(DIJKSTRA_FAILED_ALLOC);
    }

    // fill arrays with default values
    for(i = 0; i < graph->nodes; i++) {
        distance[i] = FLT_MAX;  // FLT_MAX should be enough
        seen[i] = UNSEEN;
        prev[i] = PREV_UNKNOWN;
    }

    // add pair (0, begin) to pq
    add_to_pq(pq, 0.0, begin);
    // set 0 distance to begin node
    distance[begin] = 0.0;
    prev[begin] = begin;
    // set current node as begin for correct entry into the loop
    current.node = begin; 

    // dijkstras algorithm
    while(!is_empty(pq) && current.node != end) {   // while pq is not empty and end node is not reached
        current = get_from_pq(pq);                      // take node with the smallest weight from pq
        seen[current.node] = SEEN;                      // mark current node as seen - current distance to this node is shortest distance to it
        for(i = 0; i < ADJ_LIST_COLS; i++) {            // examine adjacent vertices
            examined = graph->edge[current.node][i];        // take neighbour of current node
            if(examined.node == DEFAULT_NODE || seen[examined.node] == SEEN)
                continue;   // when there is no connection or shortest path is already known

            new_distance = distance[current.node] + examined.weight;    // set potential new distance to examined node
            if(distance[examined.node] > new_distance) {                // check if potential new distance is less than currently known one
                distance[examined.node] = new_distance;                     // yes - save new distance to known distances array
                prev[examined.node] = current.node;                         // set previous node through shortest path leads by
                add_to_pq(pq, new_distance, examined.node);                 // add examined node and its new distance to pq
            }
        }   
    } 

    // if loop has been completed due to reaching the end vertex - shortest path was found
    // in other case - there is no connection between given nodes so result is infinity (FLT_MAX)
    if(current.node == end) result = distance[current.node];
    else result = DBL_MAX; 

    //print_distances_arr(distance, graph->nodes);
    //print_prev_arr(prev, graph->nodes);

    // show detailed courese on request
    if(show_backtrace) backtrace(distance, prev, begin, end);

    // free dynamicly allocated memory
    free(distance);
    free(seen);
    if( mode == SPLIT_MODE ) {
        to_split = prev;
    }
    else 
        free(prev);

    free_pq(pq);

    return result;
}