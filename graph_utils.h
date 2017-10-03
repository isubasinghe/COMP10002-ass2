#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define INF 999

typedef struct {
    char * key;
    char * visited_from;
    int in_visited_list;
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

void graph_set(graph_t * graph, char * start);

void graph_set(graph_t * graph, char * start) {
    int srow, scol;
    loc_to_ints(start, &srow, &scol);

    node_t ** unvisited_set = malloc(graph->size_cols * graph->size_rows*sizeof(node_t *));

    free(unvisited_set);
}




    







}