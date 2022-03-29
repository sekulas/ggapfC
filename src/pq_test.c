#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "priority_queue.h"

int main(int argc, char **argv) {
    int n;                  // number of nodes
    double r;               // random number
    double min, max;        // rand range
    pq_t * pq = init_pq();  // priority_queue
    if(pq == NULL) {
        fprintf(stderr, "Something went wrong in init_pq()\n");
        return EXIT_FAILURE;
    }
    
    n = argc >= 2 ? atoi(argv[1]) : 10;
    min = argc >= 3 ? atof(argv[2]) : .0;
    max = argc >= 4 ? atof(argv[3]) : 100.0;

    srand(69);

    for(int i = 0; i < n; i++) {
        r = min + rand() / ((RAND_MAX / (max - min + 1.0)) + 1.0);
        r = (int)(r * 100.0) / 100.0;   // 2 decimal places

        if(!add_to_pq(pq, r, i)) {
            printf("Adding to pq failed!\n");
            return EXIT_FAILURE;
        }
    }
    printf("pq after filling with %d random values from %g to %g:\n", n, min, max);
    printf("pq.size : %d, pq.capacity: %d\n", pq->size, pq->capacity);
    show_pq(pq);

    printf("\np1 - root taken out\n");
    pair_t p1 = get_from_pq(pq);
    printf("p1(%g, %d)\n", p1.weight, p1.node);
    printf("pq after get operation:\n");
    printf("pq.size : %d, pq.capacity: %d\n", pq->size, pq->capacity);
    show_pq(pq);

    printf("\np2 - root taken out\n");
    pair_t p2 = get_from_pq(pq);
    printf("p2(%g, %d)\n", p2.weight, p2.node);
    printf("pq after get operation:\n");
    printf("pq.size : %d, pq.capacity: %d\n", pq->size, pq->capacity);
    show_pq(pq);

    // z testow ktore przeprowadzilem wynika ze na ogol dodadwanie do kolejki i sama kolejka
    // dziala w sposob prawidlowy, ale przy wyciaganiu sortowanie nie zawsze dziala prawidlowo
    // poprawie to w najblizszym czasie :)

    // trzeba przetestowac valgrindem

    free_pq(pq);
    return 0;
}