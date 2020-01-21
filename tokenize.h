#ifndef TOKENS_H
#define TOKENS_H

#include "vec.h"

// tokenize & read_* adapted from Lecture 9 Code
vec* tokenize(const char* text);
char* read_symbol(const char* text, int ii);
char* read_op(const char* text, int ii);
char* read_text(const char* text, int ii);

#endif
