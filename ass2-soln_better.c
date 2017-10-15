/*
 * Year 2017 : Semester 2
 * COMP10002 - Foundations of Algorithms
 *
 * Assignment 2
 *
 * Created by Isitha Subasinghe: 911584
 *
 * Algorithms are fun
 *
 */


#define READ_SIZE 16

#define LEFT 2
#define RIGHT 0
#define UP 1
#define DOWN 3

#define NEIGHBOUR_SIZE 4

#define FALSE 0
#define TRUE 1

#define CHAR2COL (-97)

#define INF 999

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


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

typedef struct {
    int * keys_int;
    char * keys_char;
    int dest_count;
} dests_t;


void create_graph(graph_t *);

void read_paths(graph_t *, int *, int*);

void read_dests(dests_t *);

void free_dests(dests_t *);

void free_graph(graph_t *);

void create_graph(graph_t * graph) {
    graph->nodes_ptrs = malloc(graph->rows * sizeof(node_t *));

    int i = 0;
    for(; i < graph->rows; i++) {
        graph->nodes_ptrs[i] = malloc(graph->cols * sizeof(node_t));
    }

}

void read_paths(graph_t * graph, int * not_pos, int *tot_costs) {
    int to_read = graph->rows * graph->cols;
    for(; to_read > 0; to_read--) {
        int keyi;
        char keyc;
        int * costs = malloc(NEIGHBOUR_SIZE*sizeof(int));
        scanf(" %d%c %d %d %d %d", &keyi, &keyc,
              &costs[RIGHT], &costs[UP], &costs[LEFT], &costs[DOWN]);
        int i = 0;
        for(; i < NEIGHBOUR_SIZE; i++) {
            if(costs[i] < INF) {
                (*tot_costs) += costs[i];
            }else {
                (*not_pos)++;
            }
        }
        graph->nodes_ptrs[keyc+CHAR2COL][keyi].key_int = keyi;
        graph->nodes_ptrs[keyc+CHAR2COL][keyi].key_char = keyc;
        graph->nodes_ptrs[keyc+CHAR2COL][keyi].cost = INF;
        graph->nodes_ptrs[keyc+CHAR2COL][keyi].from_int = 0;
        graph->nodes_ptrs[keyc+CHAR2COL][keyi].from_char = 'a';
        graph->nodes_ptrs[keyc+CHAR2COL][keyi].nxt_costs = costs;
    }
}

void read_dests(dests_t * dests) {
    dests->keys_int = malloc(READ_SIZE * sizeof(int));
    dests->keys_char = malloc(READ_SIZE * sizeof(char));
    dests->dest_count = 0;

    int key_int;
    char key_char;

    int mem = READ_SIZE;
    while(scanf(" %d%c", &key_int, &key_char) != EOF) {

        if(mem <= dests->dest_count) {
            dests->keys_int = realloc(dests->keys_int, mem*2*sizeof(int));
            assert(dests->keys_int != NULL);
            dests->keys_char = realloc(dests->keys_char, mem*2*sizeof(char));
            assert(dests->keys_char);
            mem = mem *2;
        }

        dests->keys_int[dests->dest_count] = key_int;
        dests->keys_char[dests->dest_count] = key_char;
        dests->dest_count++;


    }

    dests->keys_int = realloc(dests->keys_int,
                              dests->dest_count*sizeof(int));
    assert(dests->keys_int != NULL);

    dests->keys_char = realloc(dests->keys_char,
                               dests->dest_count*sizeof(char));
    assert(dests->keys_char);

}


void free_dests(dests_t * dests) {
    free(dests->keys_int);
    free(dests->keys_char);
    dests->dest_count = 0;
}


void free_graph(graph_t * graph) {
    int i = 0;
    for(; i < graph->rows; i++) {
        int j = 0;
        for(; j < graph->cols; j++) {
            free(graph->nodes_ptrs[i][j].nxt_costs);
        }
        free(graph->nodes_ptrs[i]);


    }
    free(graph->nodes_ptrs);
}

int get_min(node_t ** nodes, int n) {
    int min_i = -1;
    int min = INF;

    int i = 0;
    for(; i < n; i++) {
        if(nodes[i] != NULL) {
            if(nodes[i]->cost < min) {
                min_i = i;
                min = nodes[i]->cost;
            }
        }
    }

    return min_i;
}

node_t * get_node(graph_t * graph, node_t * node, int dir) {
    int row = node->key_char + CHAR2COL;
    int col = node->key_int;

    if(dir == RIGHT) {
        col++;
    }else if(dir == UP) {
        row--;
    }else if(dir == LEFT) {
        col--;
    }else if(dir == DOWN) {
        row++;
    }
    return &graph->nodes_ptrs[row][col];
}


void do_dijkstra(graph_t * graph, int skeyi, char skeyc) {

    int n = graph->cols * graph->rows;

    node_t ** unvisited_set = malloc(n*sizeof(node_t *));
    int u_set_count  = 0;

    int row = skeyc + CHAR2COL;
    int col = skeyi;

    graph->nodes_ptrs[row][col].cost = 0;
    graph->nodes_ptrs[row][col].from_char = skeyc;
    graph->nodes_ptrs[row][col].from_int = skeyi;

    int i = 0;
    for(; i < graph->rows; i++) {
        int j = 0;
        for(; j < graph->cols; j++) {
            unvisited_set[u_set_count] = &graph->nodes_ptrs[i][j];
            u_set_count++;
        }
    }

    while(TRUE) {
        int min_i = get_min(unvisited_set, n);
        if(min_i < 0) {
            break;
        }
        node_t * curr = unvisited_set[min_i];
        unvisited_set[min_i] = NULL;

        i = 0;
        for(; i < NEIGHBOUR_SIZE; i++) {
            if(curr->nxt_costs[i] < INF) {
                int cost = curr->cost + curr->nxt_costs[i];
                node_t * nxt = get_node(graph, curr, i);
                if(nxt->cost > cost) {
                    nxt->cost = cost;
                    nxt->from_char = curr->key_char;
                    nxt->from_int = curr->key_int;
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
            node_t * curr = &graph->nodes_ptrs[i][j];
            printf("{%d%c : [%d %d %d %d] : %d%c : %d}\n", curr->key_int, curr->key_char, curr->nxt_costs[RIGHT], curr->nxt_costs[UP], curr->nxt_costs[LEFT], curr->nxt_costs[DOWN], curr->from_int, curr->from_char, curr->cost);
        }
    }
}

int main() {
    /* debugging option */
    freopen("test_cases/test2.txt", "r", stdin);
    graph_t graph;
    scanf(" %d%d", &graph.cols, &graph.rows);

    printf("S1: grid is %d x %d, and has %d intersections\n",
           graph.cols, graph.rows, graph.rows*graph.cols);

    create_graph(&graph);

    int not_possible = 0;
    int tot_costs = 0;
    read_paths(&graph, &not_possible, &tot_costs);

    printf("S1: of %d possibilities, %d of them cannot be used\n",
           graph.rows * graph.cols*NEIGHBOUR_SIZE, not_possible);

    printf("S1: total cost of remaining possibilities is %d seconds\n",tot_costs);


    dests_t dests;
    read_dests(&dests);

    printf("%d grid locations supplied, first one is %d%c, last one is %d%c",
           dests.dest_count, dests.keys_int[0], dests.keys_char[0],
           dests.keys_int[dests.dest_count - 1],
           dests.keys_char[dests.dest_count -1]);
    printf("\n");



    do_dijkstra(&graph, 1, 'b');

    print_graph(&graph);

    free_dests(&dests);
    free_graph(&graph);

    return 0;
}