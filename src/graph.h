// stores pairs (weight, node) used in Dijkstra algorithm and priority queue
typedef struct pair {
    double weight;  // -1 by default
    int node;       // -1 by default
} pair_t;