/*
 #define STD_INPUT   0    // file descriptor for standard input
 #define STD_OUTPUT  1    // file descriptor for standard output
 #define READ        0    // read file descriptor from pipe
 #define WRITE       1    // write file descriptor from pipe
*/
/*
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <iostream>
*/

#include "pipe.h"


int piping(char com1[], char com2[])
{
    int pi[2];       /* pipe */
    int status;     /* status */
    
    //create child to run commands
    switch(fork())
    {
        case -1:
            // fork was unsuccessful
            printf( "unable to fork!\n" );
            return( -1 );
            
        case 0:
            // child process
            break;
            
        default:
            // parent process
            wait( &status );
            return( status );
    }
    
    // remainder executed by child
    
    // create pipe
    if(pipe(pi) < 0)
    {
        printf( "unable to pipe!\n" );
        return( -1 );
    }
    
    switch( fork() )
    {
        case -1:
            printf( "unable to fork!\n" );
            return( -1 );
            
        case 0:
            // CP
            close(STD_OUTPUT);
            
            // make standard output go to pipe
            dup(pi[WRITE]);
            
            close(pi[READ]);       //close file descriptors
            close(pi[WRITE]);
            
            // command one
            execvp(&com1[0], NULL);
            
            // if execvp returns, an error has occured
            printf("first exe call has failed!\n");
            return(-1);
            
        default:
            char output[40];
            // The parent process
            close(STD_INPUT);
            
            // Make std input come from pipe
            dup(pi[READ]);
            
            read(pi[0], &output, sizeof(char) * 40);
            
            close(pi[READ]);       //close file descriptors
            close(pi[WRITE]);
            
            // execute command two
            execvp(&com2[0], NULL);
            
            printf( "second execvp call failed!\n" );
            return( -1 );
    }
}


