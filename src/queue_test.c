#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "const.h"
#include "graph.h"

int main (int argc, char **argv) {

    queue_p q = NULL;

    for(int i = 0; i < argc; i++) {
        
        fprintf(stderr, "Ready?\n"); //test
        q = queue_add( q, i );
        fprintf(stderr, "SHOW ME THE FIRST ELEMENT!!! : %d\n", queue_top( q )); //test
    }

    fprintf(stderr, "*dzien po - oproznianko\n"); //test

    while( q ) {
        fprintf(stderr, "Mamy: %d\n", queue_top( q ));
        q = queue_pop( q );
        fprintf(stderr, "Popowanie!!!\n");
    }

}