#ifndef NUSH_PARSE_H
#define NUSH_PARSE_H

#include "ast.h"
#include "vec.h"

// Parse adapted from Lecture 9 Class Notes

int streq(const char* aa, const char* bb);
int find_first_index(vec* tokens, const char* tt);
int contains(vec* tokens, const char* tt);
vec* slice(vec* xs, int i0, int i1);
nush_ast* parse (vec* tokens);

#endif
