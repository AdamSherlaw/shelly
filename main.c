
#include "main.h"
#include "token.h"
#include "execution.h"



int builtin_cmds(char *** cmd) {
    if (strcmp(cmd[0][0], "exit") == 0 || strcmp(cmd[0][0], "quit") == 0) {
        printf("%s", "--- END ---");
        exit(0);
    } else if (strcmp(cmd[0][0], "help") == 0) {
        printf("%s\n", "HELP MESSAGE HERE");
        return 0;
    } else if (strcmp(cmd[0][0], "cd") == 0) {
        change_directory("..");
        return 0;
    } else return 1;
}


/* Main structure:
 *
 */
int main() {
    char data[512];
    char *** cmd = (char ***)malloc(sizeof(char **) * 20);
    char ** operators = (char **)malloc(sizeof(char *) * 20);
    int status;
    
    while(1) {
        read(0, data, sizeof data); /* Read the input data */
        
        /* Tokenise data - returns number of arrays in cmd */
        int array_index = tokenise(data, cmd, operators);
        
        if (builtin_cmds(cmd) == 0) continue;
        
        if (fork() == 0) pre_execute(cmd, operators, array_index, 0);
        wait(&status);
        
        printf("\n");
    }
    exit(0);
}
