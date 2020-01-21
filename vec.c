// Adapted from CS3650 HW04 Starter Code/ Lecture 9 Code
// Author: Nat Tuck

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "vec.h"

/*
typedef struct vec {
    char** data;
    int size;
    int cap;
} vec;
*/

vec*
make_vec()
{
    vec* xs = malloc(sizeof(vec));
    xs->data = malloc(4 * sizeof(char*));
    xs->size = 0;
    xs->cap  = 4;
    memset(xs->data, 0, 4 * sizeof(char*));
    return xs;
}

void
free_vec(vec* xs)
{
    for (int ii = 0; ii < xs->size; ++ii) {
        if(xs->data[ii] != 0) {
            free(xs->data[ii]);
        }
    }
    free(xs->data);
    free(xs);
}

char*
vec_get(vec* xs, int ii)
{
    assert(ii >= 0 && ii < xs->size);
    return xs->data[ii];
}

void
vec_put(vec* xs, int ii, char* xx)
{
    assert(ii >= 0 && ii < xs->size);
    xs->data[ii] = strdup(xx);
}


void
push_vec(vec* xs, char* xx)
{
    int ii = xs->size;
    if (ii >= xs->cap) {
        xs->cap *= 2;
        xs->data = (char**) realloc(xs->data, xs->cap * sizeof(char*));
    }
    xs->size = ii+1;
    vec_put(xs, ii, xx);
}

