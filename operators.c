#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "vec.h"
#include "ast.h"

int
base_case(vec* cmd) {

    int cpid;

    if ((cpid = fork())) {
        int status;
        waitpid(cpid, &status, 0);
        return WEXITSTATUS(status);
    }
    else {
        char* args[cmd->size + 1];

        for (int ii = 0; ii < cmd->size; ++ii) {
            args[ii] = cmd->data[ii];
        }
        args[cmd->size] = 0;

        execvp(args[0], args);
    }
}

// redirect* adapted from Lecture 9 notes

int
redirectout(nush_ast* ast) {
    int cpid;
    if ((cpid = fork())) {
        int status;
        waitpid(cpid, &status, 0);
        return WEXITSTATUS(status);
    }
    else {
        int fd = open(ast->arg1->cmd->data[0], O_CREAT | O_TRUNC | O_WRONLY, 0644);
        close(1);
        dup(fd);
        close(fd);

        int rv = ast_eval(ast->arg0);
        _exit(rv);
    }
}

int
redirectin(nush_ast* ast) {
    int cpid;
    if ((cpid = fork())) {
        int status;
        waitpid(cpid, &status, 0);
        return WEXITSTATUS(status);
    }
    else {
        int fd = open(ast->arg1->cmd->data[0], O_RDONLY);
        close(0);
        dup(fd);
        close(fd);

        int rv = ast_eval(ast->arg0);
        _exit(rv);
    }
}

int
background(nush_ast* ast) {
    int cpid;
    if ((cpid = fork())) {
        return ast_eval(ast->arg1);

    } else {
        int rv = ast_eval(ast->arg0);
        _exit(rv);
    }
}

// pipeto adapted from pipe class notes

int
pipeto(nush_ast* ast) {
    int cpid;
    if ((cpid = fork())) {
        int status;
        waitpid(cpid, &status, 0);
    } else {
        int pipe_fds[2];
        pipe(pipe_fds);
        int p_read = pipe_fds[0];
        int p_write = pipe_fds[1];
        int cpid2;
            if ((cpid2 = fork())) {
                int status2;
                waitpid(cpid, &status2, 0);
                close(0);
                dup(p_read);
                close(p_write);
                return ast_eval(ast->arg1);
            } else {
                close(1);
                dup(p_write); 
                close(p_read);
                int rv = ast_eval(ast->arg0);
                exit(rv);
            }
    }
}

// Attribution for _exit():
// https://stackoverflow.com/questions/2329640/how-to-exit-a-child-process-exit-vs-exit
