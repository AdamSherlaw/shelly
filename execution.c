#include "execution.h"

void execute(char ** cmd) {
    if (execvp(cmd[0], cmd) == -1) {
        printf("%s %s %s", "Command '", cmd[0], "' Not Found");
        exit(0);
    }
}


/* index is used as start point */
void pre_execute(char ** cmd, char ** operators, int length, int index) {
    int i = index; int pipes[2];
    
    if (i <= length) { /* For each command array */
        switch (operators[i][0]) {
            default:
                execute(&cmd[i]);
                break;
                
            case '|':
                pipe(pipes); /* Create pipe */
                
                if (fork() == 0) { /* Child process */
                    dup2(pipes[0], 0); /* Replace std input with input of pipe */
                    close(pipes[1]); /* Close unused half */
                    pre_execute(cmd, operators, length, index + 1);
                    exit(0);
                }
                else { /* Parent process */
                    dup2(pipes[1], 1); /* replace std output with output of pipe */
                    close(pipes[0]); /* Close unused half */
                    execute(&cmd[i]);
                }
                break;
                
            case '<':  /* Read input from file */
                printf("%s %s\n", "Opening File: ", cmd[i + 1]);
                int in;
                
                /* Ensure that the file can be opened / accessed */
                if ((in = open(cmd[i + 1], O_RDONLY)) == -1) {
                    printf("%s %s\n","Unable to open file: ", cmd[i + 1]);
                    return;
                }
                
                dup2(in, 0); /* Replace std in with file */
                close(in);  /* Close unused fd */
                
                /* If output to go to another process, fork and pipe
                   Else, output to stdout */
                if (operators[i + 1][0] == '|' || operators[i+1][0] == '>') {
                    pipe(pipes); /* Create pipe */
                    
                    /* Child process */
                    if (fork() == 0) {
                        dup2(pipes[0], 0); /* Replace std input with input pipe */
                        close(pipes[1]); /* Close unused half */
                        pre_execute(cmd, operators, length, index + 2);
                        exit(0);
                    } else
                    { /* Parent process */
                        dup2(pipes[1], 1); /* replace std output with output pipe */
                        close(pipes[0]); /* Close unused half */
                        execute(&cmd[i]);
                    }
                } else {
                    if (fork() == 0) execute(&cmd[i]);
                    else exit (0);
                } break;
                
                
            case '>': {
                /* Open the output file */
                int out;
                
                if ((out = open(cmd[i + 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1) {
                    printf("%s %s", "Unable to open file: ", cmd[i + 1]);
                    return;
                }
                
                if (fork() == 0) {
                    dup2(out, 1);  /* replace standard output with output file */
                    close(out); /* Close unused fd */
                    execute(&cmd[i]); /* Execute command */
                }
                exit(0);
                break;
            }
        }
    }
}
