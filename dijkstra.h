
#include <stdio.h>

typedef struct {
    /* although the method of storing by integer and char
    is tedious, it saves memory*/
    int key_int;
    char key_char;
    int from_int;
    char from_char;
    int * nxt_costs;
    int cost;
} node_t;
 
typedef struct {
    node_t ** nodes_ptrs;
    int rows, cols;
} graph_t;

int get_min(node_t ** nodes, int size) {
    /* store the maximum value we can have */
    int min = INF;
    int min_i = -1;
    int i = 0;
    for(; i < size; i++) {
        /* ensure that the node isn't empty */
        if(nodes[i] != NULL) {
            if((*nodes[i]).cost < min) {
                /* update the values */
                min = (*nodes[i]).cost;
                min_i = i;
            }
        }
    }
    return min_i;
 }

 node_t * get_node(int dir, graph_t * graph, node_t * node) {
     int row, col;
     row = node->key_int;
     col = node->key_char - 97;

    if(dir == LEFT) {
        col--;
    }else if(dir == RIGHT) {
        col++;
    }else if(dir == UP) {
        row--;
    }else if(dir == DOWN) {
        row++;
    }
    return &graph->nodes_ptrs[row][col];
 }

void do_dijkstra(graph_t * graph, int key_int, char key_char) {

    int srow, scol;
    srow = key_int;
    scol = key_char - 97;

    graph->nodes_ptrs[srow][scol].cost = 0;
    graph->nodes_ptrs[srow][scol].from_int = key_int;
    graph->nodes_ptrs[srow][scol].from_char = key_char;

    /* hold the unvisited vertices */
    node_t ** unvisited_set = malloc(graph->cols*graph->rows*sizeof(node_t *));
    int u_s_i = 0;

    /* we dont want to mutate the strucuture of the graph, 
    so we take a 1D copy of the pointers*/
    int i = 0;
    for(; i < graph->rows; i++) {
        int j =0;
        for(; j < graph->cols; j++) {
            unvisited_set[u_s_i] = &graph->nodes_ptrs[i][j];
            u_s_i++;
        }
    }

    /* when we do this time goes from O(n*(n+2)) to O(n^2), 
    since we do no need to loop to check if unvisited_set is 
    empty*/
    int unvisited_count = graph->cols * graph->rows;

    for(; unvisited_count > 0; unvisited_count--) {
        int min_node_i = get_min(unvisited_set, graph->cols * graph->rows);
        /* really shouldn't get here unless malformed input was given*/
        if(i < 0) {
            break;
        }
        node_t * curr = unvisited_set[min_node_i];
        unvisited_set[min_node_i] = NULL;

        int i = 0;
        for(; i < NEIGHBOUR_SIZE; i++) {
            if(curr->nxt_costs[i] < INF) {
                node_t * nxt_node = get_node(i, graph, curr);
                int cost = curr->cost + curr->nxt_costs[i];
                if(cost < nxt_node->cost) {
                    nxt_node->cost = cost;
                    nxt_node->from_int = curr->key_int;
                    nxt_node->from_char = curr->key_char;
                }

            }
        }


    }

    free(unvisited_set);
}

void print_graph(graph_t * graph) {
    int i = 0;
    for(; i < graph->rows; i++) {
        int j = 0;
        for(; j < graph->cols; j++) {
            printf("%d%c %d\n", graph->nodes_ptrs[i][j].key_int, graph->nodes_ptrs[i][j].key_char, graph->nodes_ptrs[i][j].cost);
        }
    }
}