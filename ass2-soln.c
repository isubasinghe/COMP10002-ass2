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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    char ** tokens;
    unsigned int token_count;
} tokens_container_t;

typedef struct {
    unsigned int left;
    unsigned int right;
    unsigned int up;
    unsigned int down;
} node_t;

typedef struct {
    node_t ** nodes;
    unsigned int size_x;
    unsigned int size_y;
} graph_t;

int mygetchar();

char * read_line();

tokens_container_t get_tokens(char *, char *);

graph_t create_graph(unsigned int, unsigned int);

void free_graph(graph_t);

int mygetchar() {
    int c = getchar();
    while(c == '\r') {
        c = getchar();
    }
    return c;
}

char * read_line() {

    int c = mygetchar();

    char * text = malloc(sizeof(char)*1024);

    if (c == '\n') {
       free(text);
       return read_line();
    }
    assert(text != NULL);

    unsigned int text_index = 0;

    while(c != '\n' && c != EOF) {

        if(text_index%1023 ==0) {
            text = realloc(text, sizeof(char) * (text_index+1024));
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

tokens_container_t get_tokens(char * string, char * delim) {
    tokens_container_t tokens_c;
    /* 
    We only need 5 at most,
    the max will occur at a line like
    0a      99 9 9 3
    I used 8 because it is a power of two.
    */
    tokens_c.tokens = malloc(8*sizeof(char *));
    assert(tokens_c.tokens != NULL);
    tokens_c.token_count = 0;

    char * token = strtok(string, delim);
    while(token != NULL) {
        assert(tokens_c.token_count < 8);
        tokens_c.tokens[tokens_c.token_count] = token;
        tokens_c.token_count++;
        token = strtok(NULL, delim);
    }
    


    return tokens_c;
}

graph_t create_graph(unsigned int x, unsigned int y) {
    graph_t graph;

    node_t ** nodes_ptrs = malloc(x * sizeof(node_t *));
    int i = 0;
    for(; i < x; i++) {
        node_t * nodes = malloc(y * sizeof(node_t));
        assert(nodes != NULL);
        nodes_ptrs[i] = nodes;
        i++; 
    }
    assert(nodes_ptrs != NULL);
    graph.nodes = nodes_ptrs;
    graph.size_x = x;
    graph.size_y = y;
    return graph;
}



void free_graph(graph_t graph) {

}

int main(int argc, char *argv[]) {

    char * line = read_line();
    tokens_container_t tc = get_tokens(line, " ");
    assert(tc.token_count == 2);
    int cols = atoi(tc.tokens[0]);
    int rows = atoi(tc.tokens[1]);
    assert(rows > 0 && cols > 0);
    printf("S1: grid is %d x %d, and has %d intersections\n", rows, cols, rows*cols);
    free(line);
    free(tc.tokens);
    tc.tokens = NULL;
    tc.token_count = 0;


    unsigned int possible_paths = 0;
    unsigned int not_possible_paths = 0;
    unsigned int total_cost = 0;

    graph_t graph = create_graph(rows, cols);

    while((line = read_line()) != NULL) {
        tc = get_tokens(line, " ");
        
        free(tc.tokens);
        tc.tokens = NULL;
        tc.token_count = 0;


    }


    return 0;
}