#ifndef NUSH_AST_H
#define NUSH_AST_H

// Adapted from CALC_AST_H Lecture Notes

#include <stdlib.h>
#include "vec.h"

typedef struct nush_ast {
    char* op;
    struct nush_ast* arg0;
    struct nush_ast* arg1;
    vec* cmd;

} nush_ast;

nush_ast* make_ast_cmd(vec* cmd);
nush_ast* make_ast_op(char* op, nush_ast* a0, nush_ast* a1);
void free_ast(nush_ast* ast);
int ast_eval(nush_ast* ast);

#endif
