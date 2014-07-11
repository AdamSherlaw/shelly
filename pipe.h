#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <iostream>

#include <readline/readline.h>
#include <readline/history.h>


#define STD_INPUT   0    /* file descriptor for standard input  */
#define STD_OUTPUT  1    /* file descriptor for standard output */
#define READ        0    /* read file descriptor from pipe  */
#define WRITE       1    /* write file descriptor from pipe */


int piping(char com1[], char com2[]);
