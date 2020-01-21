#include <stdio.h>
#include <string.h>

#include "vec.h"
#include "ast.h"
#include "parse.h"

// Adapted from lecture 9 class notes

int
streq(const char* aa, const char* bb)
{
    return strcmp(aa, bb) == 0;
}

int
find_first_index(vec* tokens, const char* tt)
{
    for (int ii = 0; ii < tokens->size; ++ii) {
        if (streq(tokens->data[ii], tt)) {
            return ii;
        }
    }
    return -1;
}

int
contains(vec* tokens, const char* tt)
{
    return find_first_index(tokens, tt) >= 0;
}

vec*
slice(vec* xs, int i0, int i1)
{
    vec* ys = make_vec();
    for (int ii= i0; ii< i1; ++ii) {
        push_vec(ys, xs->data[ii]);
    }
    return ys;
}

nush_ast*
parse (vec* tokens)
{
    char* ops[] = {">", "<", "|", "&", "||", "&&", ";"};

    for (int ii = 0; ii < 7; ++ii) {
        char* op = ops[ii];

        if (contains(tokens, op)) {
            int jj = find_first_index(tokens, op);
            vec* xs = slice(tokens, 0, jj);
            vec* ys = slice(tokens, jj+1, tokens->size);
            nush_ast* ast = make_ast_op(op, parse(xs), parse(ys));
            free_vec(xs);
            free_vec(ys);
            return ast;
        }
    }
    return make_ast_cmd(tokens);
}
