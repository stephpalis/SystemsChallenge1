
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ast.h"
#include "operators.h"

/*
typedef struct nush_ast {
    char* op;
    struct nush_ast* arg0;
    struct nush_ast* arg1;
    vec* cmd;

} nush_ast;
*/

// Adapted from Lecture 9 ast.c notes

nush_ast* 
make_ast_cmd(vec* cmd)
{
    nush_ast* ast = malloc(sizeof(nush_ast));
    ast->op = ";";
    ast->arg0 = 0;
    ast->arg1 = 0;
    ast->cmd = make_vec();
    for(int ii = 0; ii< cmd->size; ++ii) {
        push_vec(ast->cmd, cmd->data[ii]);
    }
    return ast;
}

nush_ast* 
make_ast_op(char* op, nush_ast* a0, nush_ast* a1)
{
    nush_ast* ast = malloc(sizeof(nush_ast));
    ast->op = op;
    ast->arg0 = a0;
    ast->arg1 = a1;
    ast->cmd = 0;
    return ast;
}

void 
free_ast(nush_ast* ast)
{
    if (ast) {
        if (ast->arg0) {
            free_ast(ast->arg0);
        }

        if (ast->arg1) {
            free_ast(ast->arg1);
        }

        if (ast->cmd) {
            free_vec(ast->cmd);
        }

        free(ast);
    }
}

int
ast_eval(nush_ast* ast)
{
    if (ast == 0) {
        return 1;
    }

    if (ast->arg0 == 0 && ast->arg1 == 0) {
        if (ast->cmd->data[0] == 0) {
            return 1;
        }
        
        if (strcmp(ast->cmd->data[0], "cd") == 0) {
            chdir(ast->cmd->data[1]);
            return 0;
        }

        if (strcmp(ast->cmd->data[0], "exit") == 0) {
            free_ast(ast);
            exit(0);
        } 

        return base_case(ast->cmd);
    }

    char* op = ast->op;
    if (strcmp(op, ";") == 0) {
        ast_eval(ast->arg0);
        ast_eval(ast->arg1);

    } else if (strcmp(op,"<") == 0) {
        return redirectin(ast);

    } else if (strcmp(op, ">") == 0) {
        return redirectout(ast);

    } else if (strcmp(op, "|") == 0) {
        return pipeto(ast); 
    
    } else if (strcmp(op, "&") == 0) {
        return background(ast); 

    } else if (strcmp(op, "&&") == 0) {
        int rv = ast_eval(ast->arg0);
        if (rv == 0) {
            return ast_eval(ast->arg1);
        }
    } else if (strcmp(op, "||") == 0) {
        int rv = ast_eval(ast->arg0);
        if (rv != 0) {
            return ast_eval(ast->arg1);
        }
    } else {
        printf("Undefined token");
        exit(1);
    }
}
