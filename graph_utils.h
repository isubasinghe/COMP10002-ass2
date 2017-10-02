typedef struct {
    char * key;
    char * visited_from;
    int left;
    int right;
    int up;
    int down;
    int cost;
} node_t;

typedef struct {
    node_t ** nodes_ptrs;
    int size_rows;
    int size_cols;
} graph_t;

void graph_set(graph_t *graph, char * start, char * end, char ** visited, int size) {
    int srow, scol;
    loc_to_ints(start, &srow, &scol);
    
    node_t prev_node = graph->nodes_ptrs[srow][scol];
    prev_node.cost = 0;

    int * order = get_order(node);
    
}