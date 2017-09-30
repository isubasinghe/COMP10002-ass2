/*
 * Year 2017 : Semester 2
 * COMP10002 - Foundations of Algorithms
 * 
 * Assignment 2
 *
 * Created by Isitha Subasinghe: 911584
 * 
 * Algorithms are fun
 */

 #define LEFT 0
 #define RIGHT 1
 #define UP 2
 #define DOWN 3

 #define INF 999

 #define READ_SIZE 512
 #define MAX_TOKS 5

 #define MAX_TENSOR_DIM 2

 #define MAX_DEST_TOKS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    char ** tokens;
    int token_count;
} tokens_arr_t;

typedef struct {
    char ** dests;
    int dest_count;
} dests_t;

typedef struct {
    int left;
    int right;
    int up;
    int down;
} node_t;

typedef struct {
    node_t ** nodes_ptrs;
    int size_rows;
    int size_cols;
} graph_t;

int mygetchar();

char * read_line();

tokens_arr_t get_tokens(char *, char *);

graph_t create_graph(int, int);

void insert_to_graph(graph_t *, tokens_arr_t, int *, int *);

void read_to_graph_and_dests(graph_t *, dests_t *, int *, int *);

void free_graph(graph_t *);

void my_A_star(graph_t * graph, char * loc);

int mygetchar() {
    int c = getchar();
    while(c == '\r') {
        c = getchar();
    }
    return c;
}

char * read_line() {

    int c = mygetchar();

    char * text = malloc(sizeof(char)*READ_SIZE);
    /* ignore the empty lines */
    if (c == '\n') {
       free(text);
       return read_line();
    }
    assert(text != NULL);

    int text_index = 0;

    while(c != '\n' && c != EOF) {

        if(text_index%(READ_SIZE-1) ==0) {
            text = realloc(text, sizeof(char) * (text_index+READ_SIZE));
            assert(text != NULL);

        }

        text[text_index] = (char)c;
        text_index++;
        c = mygetchar();

    }

    text[text_index] = '\0';

    if(text_index == 0) {
        free(text);
        return NULL;
    }

    return text;
}

tokens_arr_t get_tokens(char * string, char * delim) {
    tokens_arr_t tokens_c;
    /* 
    We only need 5 at most,
    the max will occur at a line like
    0a      99 9 9 3
    I used 8 because it is a power of two.
    */
    tokens_c.tokens = malloc(MAX_TOKS*sizeof(char *));
    assert(tokens_c.tokens != NULL);
    tokens_c.token_count = 0;

    char * token = strtok(string, delim);
    while(token != NULL) {
        assert(tokens_c.token_count < MAX_TOKS);
        tokens_c.tokens[tokens_c.token_count] = token;
        tokens_c.token_count++;
        token = strtok(NULL, delim);
    }
    return tokens_c;
}

graph_t create_graph(int rows, int cols) {
    graph_t graph;
    /* create a matrix to represent the city */
    node_t ** nodes_ptrs = malloc(rows * sizeof(node_t *));
    int i = 0;
    for(; i < rows; i++) {
        node_t * nodes = malloc(cols * sizeof(node_t));
        assert(nodes != NULL);
        nodes_ptrs[i] = nodes;
    }
    assert(nodes_ptrs != NULL);
    graph.nodes_ptrs = nodes_ptrs;
    graph.size_rows = rows;
    graph.size_cols = cols;
    return graph;
}

void insert_to_graph(graph_t * graph, tokens_arr_t tc, 
        int * n_ps_paths, int * total_cost) {

    int row = tc.tokens[0][strlen(tc.tokens[0])-1] - 97;
    tc.tokens[0][strlen(tc.tokens[0])-1] = '\0';
    int col = atoi(tc.tokens[0]);

    node_t node;
    node.right = atoi(tc.tokens[1]);
    node.up = atoi(tc.tokens[2]);
    node.left = atoi(tc.tokens[3]);
    node.down = atoi(tc.tokens[4]);
    
    graph->nodes_ptrs[row][col] = node;

    int i=1;
    for(; i < tc.token_count; i++) {
        int curr_int = atoi(tc.tokens[i]);
        if(curr_int < INF) {
            (*total_cost) += curr_int;
        }else {
            (*n_ps_paths)++;
        }
    }

}

void read_to_graph_and_dests(graph_t * graph, dests_t * dests, 
        int * n_pos_paths, int * tot_cost) {
    char * line;
    while((line = read_line()) != NULL) {
        tokens_arr_t tc;
        tc = get_tokens(line, " ");
        
        if(tc.token_count == MAX_TOKS) {
            insert_to_graph(graph, tc, n_pos_paths, tot_cost);
        }else if (tc.token_count == MAX_DEST_TOKS) {
            
        }else {
            printf("Malformed input\n");

        }

        free(tc.tokens);
        tc.tokens = NULL;
        tc.token_count = 0;
    }
}

void free_graph(graph_t * graph) {
    int i = 0;
    for(; i < graph->size_rows; i++) {
 
        free(graph->nodes_ptrs[i]);
    }
    free(graph->nodes_ptrs);
}

int main(int argc, char *argv[]) {

    char * line = read_line();
    tokens_arr_t tc = get_tokens(line, " ");
    assert(tc.token_count == MAX_TENSOR_DIM);
    int cols = atoi(tc.tokens[0]);
    int rows = atoi(tc.tokens[1]);
    assert(rows > 0 && cols > 0);
    printf("S1: grid is %d x %d, and has %d intersections\n", cols, rows, rows*cols);
    free(line);
    free(tc.tokens);
    tc.tokens = NULL;
    tc.token_count = 0;

    graph_t graph = create_graph(rows, cols);
    dests_t dests;

    int not_possible_paths = 0;
    int total_cost = 0;
    read_to_graph_and_dests(&graph, &dests, &not_possible_paths, &total_cost);

    printf("S1: of %d possibilities, %d of them cannot be used\n", rows*cols*4, not_possible_paths);
    printf("S1: total cost of remaining possibilities is %d seconds\n", total_cost);



    free_graph(&graph);


    return 0;
}