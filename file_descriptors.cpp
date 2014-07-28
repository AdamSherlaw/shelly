//
//  file_descriptors.cpp
//
//
//  Created by Adam Sherlaw on 14/07/14.
//
//

#include "file_descriptors.h"
#include <unistd.h>


#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    /*char buff[12];
     int pi[2];
     int n;
     
     
     
     int in;
     int out;
     
     
     
     out = 3;//dup(1);
     in = 2;//dup(0);
     
     
     while ((n = read(0, buff, sizeof buff)) > 0) {
     std::cout<<"1: " << n<< buff<<std::endl;
     write(out, buff, n);
     }
     
     close(0);
     
     n = read(in, buff, sizeof buff);
     std::cout<<"2: " << n<<std::endl;
     write(1, buff, n);
     
     
     
     exit(0);
     */
    
    
    
    
    int pfd[2];
    pid_t cpid;
    char buf;
    
    assert(argc == 2);
    
    
    /* Pipe creates a pair of file descriptors */
    if (pipe(pfd) == -1) { perror("pipe"); exit(EXIT_FAILURE); }
    
    
    cpid = fork();
    if (cpid == -1) { perror("fork"); exit(EXIT_FAILURE); }
    
    
    if (cpid == 0) {    /* Child reads from pipe */
        close(pfd[1]);          /* Close unused write end */
        
        write(STDOUT_FILENO, "Here \n", 10);
        while (read(pfd[0], &buf, 1) > 0) {
            
            write(STDOUT_FILENO, &buf, 1);
        }
        
        write(STDOUT_FILENO, "\n", 1);
        close(pfd[0]);
        _exit(EXIT_SUCCESS);
        
        
    } else {            /* Parent writes argv[1] to pipe */
        close(pfd[0]);          /* Close unused read end */
        write(STDOUT_FILENO, "Here2 \n", 10);
        write(pfd[1], argv[1], strlen(argv[1]));
        close(pfd[1]);          /* Reader will see EOF */
        wait(NULL);             /* Wait for child */
        exit(EXIT_SUCCESS);
    }
}



