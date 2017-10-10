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
 * Note: This project was imported from a previous version
 * using a custom scanf functionality, therfore there may be some
 * redundencies.
 */

 #define READ_SIZE 16

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define NEIGHBOUR_SIZE 4

#define INF 999

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int * keys_int;
    char * keys_char;
    int dest_count;
} dests_t;

typedef struct {
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

    int i = 0;
    for(; i < graph->rows; i++) {
        int j = 0;
        for(; j < graph->cols; j++) {
            
            int key1;
            char key2;
            int * nxt_costs = malloc(NEIGHBOUR_SIZE * sizeof(int));
            
            scanf(" %d%c %d %d %d %d", &key1, &key2, 
                &nxt_costs[0], &nxt_costs[1], &nxt_costs[2], &nxt_costs[3]);
            int z = 0;
            for(; z < NEIGHBOUR_SIZE; z++) {
                if(nxt_costs[z] < 999) {
                    (*tot_costs) += nxt_costs[z];
                }else {
                    (*not_pos)++;
                }
            }
            graph->nodes_ptrs[i][j].key_int = key1;
            graph->nodes_ptrs[i][j].key_char = key2;
            graph->nodes_ptrs[i][j].nxt_costs = nxt_costs;
            graph->nodes_ptrs[i][j].cost = INF;

        }
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

void get_rows_cols(int * row, int * col, int key_int, char key_char) {
    (*row) = key_char - 97;
    (*col) = key_int;
}

void dijkstra(graph_t * graph, int skey_int, char skey_char) {
    int row, col;
    get_rows_cols(&row, &col, skey_int, skey_char);

    graph->nodes_ptrs[row][col].cost = 0;
    graph->nodes_ptrs[row][col].from_int =  graph->nodes_ptrs[row][col].key_int;
    graph->nodes_ptrs[row][col].from_char =  graph->nodes_ptrs[row][col].key_char;

    /* hold the unvisited vertices */
    node_t ** unvisited_set = malloc(graph->cols*graph->rows*sizeof(node_t *));
    int u_s_i = 0;
   
    /* we dont want to mutate the strucuture of the graph, so we take a copy of it*/
    int i = 0;
    for(; i < graph->rows; i++) {
        int j =0;
        for(; j < graph->cols; j++) {
            unvisited_set[u_s_i] = &graph->nodes_ptrs[i][j];
            u_s_i++;
        }
    }

    

    free(unvisited_set);

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

int main() {
    //freopen("test_cases/test2.txt", "r", stdin);
    graph_t graph;
    scanf(" %d%d", &graph.rows, &graph.cols);

    printf("S1: grid is %d x %d, and has %d intersections\n", 
        graph.rows, graph.cols, graph.rows*graph.cols);

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


    free_dests(&dests);
    free_graph(&graph);

    return 0;
 }