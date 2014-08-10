
#include "main.h"
#include "token.h"
#include "execution.h"



int builtin_cmds(char ** cmd) {
    if (strcmp(cmd[0], "exit") == 0 || strcmp(cmd[0], "quit") == 0) {
        printf("%s", "--- END ---\n");
        return 1;
    } else if (strcmp(cmd[0], "help") == 0) {
        printf("%s\n", "Type in executable commands that are in the /bin/ folder to execute.\n");
        return 0;
    } else if (strcmp(cmd[0], "cd") == 0) {
        change_directory(cmd[1]);
        return 0;
    } else return -1;
}


/* Main structure:
 *
 */
int main() {
    char data[512];
    char ** cmd = (char **)malloc(sizeof(char *) * 20);
    char ** operators = (char **)malloc(sizeof(char *) * 20);
    int status; int builtin;
    
    while(read(0, data, sizeof data) > 0) {
        // What does read return when there is no input?
        // Don't call anything until input is present
        
        //read(0, data, sizeof data); /* Read the input data */
        
        /* Tokenise data - returns number of arrays in cmd */
        int array_index = tokenise(data, cmd, operators);
        
        builtin = builtin_cmds(cmd);
        if (builtin == 0) continue;
        if (builtin == 1) break;
        
        if (fork() == 0) pre_execute(cmd, operators, array_index, 0);
        wait(&status);
        
        printf("\n");
    }
    
    /*for (int i = 0; i < 20; i++) {
        for int j = 0; j < array_index; j++) {
            free(cmd[i][0])
        }
    }*/
    free(cmd);
    free(operators);
    exit(0);
}
