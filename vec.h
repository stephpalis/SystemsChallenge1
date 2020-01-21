// Adapted from CS3650 HW04 Starter Code / Lecture 9 Code
// Author: Nat Tuck

#ifndef VEC_H
#define VEC_H

typedef struct vec {
    char** data;
    int size;
    int cap;
} vec;

vec* make_vec();
void free_vec(vec* xs);
char* vec_get(vec* xs, int ii);
void vec_put(vec* xs, int ii, char* xx);

void push_vec(vec* xs, char* xx);

#endif
