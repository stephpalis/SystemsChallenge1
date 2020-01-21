#ifndef OPERATORS_H
#define OPERATORS_H

#include "vec.h"
#include "ast.h"

int base_case(vec* cmd);
int redirectout(nush_ast* ast);
int redirectin(nush_ast* ast);
int background(nush_ast* ast);
int pipeto(nush_ast* ast);

#endif
