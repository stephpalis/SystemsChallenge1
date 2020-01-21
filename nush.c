#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "vec.h"
#include "tokenize.h"
#include "parse.h"

int
main(int argc, char* argv[])
{
    char cmd[256];
    if (argc == 1) {
        while (1) {
            printf("nush$ ");
            fflush(stdout);
            char* err = fgets(cmd, 256, stdin);
            if (err == 0) {
                break;
            }
            vec* tokens = tokenize(cmd);
            nush_ast* nast = parse(tokens);
            free_vec(tokens);
            ast_eval(nast);
            free_ast(nast);
        }
    }
    else {
        FILE* input = fopen(argv[1], "r");
        while (1) {
            char* err = fgets(cmd, 256, input);
            if (err == 0) {
                break;
            }
            vec* tokens = tokenize(cmd);
            nush_ast* nast = parse(tokens);
            free_vec(tokens);
            ast_eval(nast);
            free_ast(nast);
        }
        fclose(input);
    }
    return 0;
}
