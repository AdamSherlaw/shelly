
#include "parse.h"


/*
 cmd[i][0]  - Gives 'n' if no other command is to be run
 - Gives '<' for redirection
 - Gives '>' for redirection
 - Gives '|' for piping into another command
 
 cmd[i] is an array that contains the command and the associated
 arguments.
 The command is at index 1 and the remaining arguments in indexes above
 1.
 
 
 Take command
 is builtin
 output redirected / piped
 execute with arguments
 */
void parse_input(char * input) {
    
}