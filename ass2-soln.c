#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
typedef struct {
    char key[10];
    unsigned int left;
    unsigned int right;
    unsigned int up;
    unsigned int down;
} corner_t;

typedef struct {
    unsigned int size_x;
    unsigned int size_y;
    corner_t * corners;
    unsigned int corners_size;
} corner_container_t;

typedef struct {
    char ** tokens;
    unsigned int size;
} tokens_container_t;

int mygetchar();

char * read_line();

char ** get_tokens(char * delim);

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

int main(int argc, char *argv[]) {

    return 0;
}