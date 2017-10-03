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

 #define SIMP_ASCII_TO_INT_DIFF (-97)

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

int mygetchar();

char * read_line();

tokens_arr_t get_tokens(char *, char *);

graph_t create_graph(int, int);

void loc_to_ints(char *, int *, int *);

void insert_to_graph(graph_t *, tokens_arr_t, int *, int *);

void read_to_graph_and_dests(graph_t *, dests_t *, int *, int *);

int get_min(node_t **, int)

int is_empty(node_t **, int);

node_t * get_node(int, graph_t *, char *);

void graph_set(graph_t *, char *);

void free_graph(graph_t *);

int mygetchar() {
    int c = getchar();
    while(c == '\r') {
        c = getchar();
    }
    return c;
}

char * read_line() {

    int c = mygetchar();
    /* store the text buffer in here */
    char * text = malloc(sizeof(char)*READ_SIZE);
    /* ignore the empty lines */
    if (c == '\n') {
       free(text);
       return read_line();
    }
    /* ensure that we had enough memory */
    assert(text != NULL);

    int text_index = 0;

    while(c != '\n' && c != EOF) {
        /* increase our memory every time READ_SIZE bytes
         * are written into text. */
        if(text_index%(READ_SIZE-1) ==0) {
            text = realloc(text, sizeof(char) * (text_index+READ_SIZE));
            assert(text != NULL);

        }

        text[text_index] = (char)c;
        text_index++;
        c = mygetchar();

    }
    /* We must always put a null terminator to
     indicate the end of a string */
    text[text_index] = '\0';
    /* This occurred becaues we found an EOF first up*/
    if(text_index == 0) {
        free(text);
        return NULL;
    }

    return text;
}

tokens_arr_t get_tokens(char * string, char * delim) {
    tokens_arr_t tokens_c;
    /* We already know the max words a line may have is MAX_TOKS*/
    tokens_c.tokens = malloc(MAX_TOKS*sizeof(char *));
    assert(tokens_c.tokens != NULL);
    tokens_c.token_count = 0;
    /* split the string by a delimiter */
    char * token = strtok(string, delim);
    /* keep on splitting until the end of the line */
    while(token != NULL) {
        /* ensure that we dont get more than MAX_TOKS tokens
         as this represent malformed input */
        assert(tokens_c.token_count < MAX_TOKS);
        tokens_c.tokens[tokens_c.token_count] = token;
        tokens_c.token_count++;
        token = strtok(NULL, delim);
    }
    return tokens_c;
}

graph_t create_graph(int rows, int cols) {
    graph_t graph;
    /* create a matrix to represent the city.
       we store a pointer to the columns here */
    node_t ** nodes_ptrs = malloc(rows * sizeof(node_t *));
    int i = 0;
    for(; i < rows; i++) {
        /* create the columns and allocate the resources for it*/
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

void loc_to_ints(char *loc, int * row, int * col) {
    /* why the fuck won't this work, malloced memory is read/write, fuck this*/
    
    /*
    (*row) = loc[strlen(loc)-1] + SIMP_ASCII_TO_INT_DIFF;

    loc[strlen(loc) - 1] = '\0';
    (*col) = atoi(loc);
    */

    char * line = strdup(loc);

    (*row) = line[strlen(line) - 1] + SIMP_ASCII_TO_INT_DIFF;
    line[strlen(line) - 1] = '\0';
    (*col) = atoi(line);

    free(line);


}

void insert_to_graph(graph_t * graph, tokens_arr_t tc, 
        int * n_ps_paths, int * total_cost) {

    int row, col;
    loc_to_ints(tc.tokens[0], &row, &col);

    node_t node;
    /* set the key of the node */
    node.key = strdup(tc.tokens[0]);
    node.right = atoi(tc.tokens[1]);
    node.up = atoi(tc.tokens[2]);
    node.left = atoi(tc.tokens[3]);
    node.down = atoi(tc.tokens[4]);
    /* we set all the values to INF */
    node.cost = INF;

    /* add the node to the matrix */
    graph->nodes_ptrs[row][col] = node;

    int i=1;
    for(; i < tc.token_count; i++) {
        int curr_int = atoi(tc.tokens[i]);
        if(curr_int < INF) {
            /* we can take this path so add the cost*/
            (*total_cost) += curr_int;
        }else {
            /* we cannot take this path so increment the 
            not possible path variable*/
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
        /* we have a received information about a node */
        if(tc.token_count == MAX_TOKS) {
            insert_to_graph(graph, tc, n_pos_paths, tot_cost);
         /* we have received information about a destination */
        }else if (tc.token_count == MAX_DEST_TOKS) {
            dests->dests[dests->dest_count] = strdup(tc.tokens[0]);
            dests->dest_count++;
        }else {
            printf("Malformed input\n");

        }
        /* free the tokens holder and the line */
        free(line);
        line = NULL;
        free(tc.tokens);
        tc.tokens = NULL;
        tc.token_count = 0;
    }
}

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

int is_empty(node_t ** nodes, int size) {
    int empty = 1;
    int i = 0;
    for(; i < size; i++) {
        if(nodes[i] != NULL) {
            empty = 0;
            break;
        }
    }
    return empty;
}

node_t * get_node(int dir, graph_t * graph, char * key) {
    int row, col;
    loc_to_ints(key, &row, &col);

    if(dir == LEFT) {
    /* if we want to move to the node by left in a matrix 
    we need to decrement the j element of the matrix */
        col--;
    }else if(dir == RIGHT) {
    /* if we want to move to the node by right in a matrix
    we need to increment the j element of the matrix */
        col++;
    }else if (dir == UP) {
    /* if we want to move the node by up in a matrix
    we need to decrement the i element of the matrix */
        row--;
    }else if(dir == DOWN) {
    /* if we want to move the node down in a matrix
    we need to increment the i element of the matrix */
        row++;
    }

    return &graph->nodes_ptrs[row][col];
}

void graph_set(graph_t * graph, char * start) {
    int srow, scol;
    loc_to_ints(start, &srow, &scol);
    /* set the initial values to the starting variables */
    graph->nodes_ptrs[srow][scol].cost = 0;
    graph->nodes_ptrs[srow][scol].visited_from = graph->nodes_ptrs[srow][scol].key;

    /* hold the unvisited vertices */
    node_t ** unvisited_set = malloc(graph->size_cols * graph->size_rows*sizeof(node_t *));
    int u_s_i = 0;
    
    /* we dont want to mutate the strucuture of the graph, so we take a copy of it*/
    int i = 0;
    for(; i < graph->size_rows; i++) {
        int j =0;
        for(; j < graph->size_cols; j++) {
            unvisited_set[u_s_i] = &graph->nodes_ptrs[i][j];
            u_s_i++;
        }
    }

    /* iterate through all the unvisited node and take them off the unvisited list*/
    while(!is_empty(unvisited_set, graph->size_cols * graph->size_rows)) {
        int min_i = get_min(unvisited_set, graph->size_cols * graph->size_rows);
        /* we should never reach here for good input but better safe than sorry*/
        if(min_i == -1) {
            break;
        }
        
        /* select the unvisited node that is marked with the smallest tentative distance */
        node_t * curr = unvisited_set[min_i];
        /* remove the current node from the unvisited set*/
        unvisited_set[min_i] = NULL;

        /* check the current nodes neighbours and check if the quickest path is through
        the current node, if so update the cost and visited_from*/

        if(curr->left < INF) {
            node_t * l_node = get_node(LEFT, graph, curr->key);
            int cost = curr->cost + curr->left;
            if(cost < l_node->cost) {
                l_node->cost = cost;
                l_node->visited_from = curr->key;
            }
            
        }

        if(curr->right < INF) {
            node_t * r_node = get_node(RIGHT, graph, curr->key);
            int cost = curr->cost + curr->right;
            if(cost < r_node->cost) {
                r_node->cost = cost;
                r_node->visited_from = curr->key;
            }
        }

        if(curr->down < INF) {
            node_t * d_node = get_node(DOWN, graph, curr->key);
            int cost = curr->cost + curr->down;
            if(cost < d_node->cost) {
                d_node->cost = cost;
                d_node->visited_from = curr->key;
            }
        }

        if(curr->up < INF) {
            node_t * u_node = get_node(UP, graph, curr->key);
            int cost = curr->cost + curr->up;
            if(cost < u_node->cost) {
                u_node->cost = cost;
                u_node->visited_from = curr->key;
            }
        }
    }

    free(unvisited_set);
}

void free_graph(graph_t * graph) {
    /* free the graphs */
    int i = 0;
    for(; i < graph->size_rows; i++) {
        /* free the key holder */
        free(graph->nodes_ptrs[i]->key);
        /* free the node*/
        free(graph->nodes_ptrs[i]);
    }
    /* free the node pointer array holder */
    free(graph->nodes_ptrs);
}

int main() {
    freopen("test_cases/test1.txt", "r", stdin);
    /* read a line to get the dimensions of our matrix */
    char * line = read_line();
    tokens_arr_t tc = get_tokens(line, " ");
    /* make sure that we are given the right amount of dimensions */
    assert(tc.token_count == MAX_TENSOR_DIM);
    /* convert the integer sequence to actual integers*/
    int cols = atoi(tc.tokens[0]);
    int rows = atoi(tc.tokens[1]);
    assert(rows > 0 && cols > 0);

    printf("S1: grid is %d x %d, and has %d intersections\n", cols, rows, rows*cols);

    /* free the token holders */
    free(line);
    free(tc.tokens);
    tc.tokens = NULL;
    tc.token_count = 0;

    /* create a rows * cols matrix */
    graph_t graph = create_graph(rows, cols);
    dests_t dests;
    dests.dest_count = 0;

    /* just malloc the most possible destinations we can have */
    dests.dests = malloc(rows*cols*sizeof(char *));
    assert(dests.dests != NULL);

    /* store the variables for stage 1 in here */
    int not_possible_paths = 0;
    int total_cost = 0;

    /* read the data into the graph and dests variables */
    read_to_graph_and_dests(&graph, &dests, &not_possible_paths, &total_cost);

    printf("S1: of %d possibilities, %d of them cannot be used\n", rows*cols*4, not_possible_paths);
    printf("S1: total cost of remaining possibilities is %d seconds\n", total_cost);

    printf("S1: %d grid locations supplied, first one is %s, last one is %s\n", 
        dests.dest_count, dests.dests[0], dests.dests[dests.dest_count-1]);

    /* get all the shortest paths to every other destinations from arg1 */
    graph_set(&graph, "0a");


    /* free the graphs and dests */
    free(dests.dests);
    free_graph(&graph);


    return 0;
}