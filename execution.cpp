
#include "execution.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


using namespace std;

/*char * arguments(char * input) {
 char *args = (char *)malloc(sizeof(char *) * 512);
 
 for (int i = 2; i <= strlen(input); i++) {
 //cout << "i: " << input[i] << endl;
 args[i] = input[i];
 cout << "i: " << args[i] << endl;
 }
 return args;
 }*/


void execute_command(char * cmd_name, char ** args) {
    /* pid_t data type - Signed integer type which is capable of representing a
     process ID - In the GNU Lib this is an int.
     
     Fork() creates a copy of the current process.
     - Returns a negative value if the creation of child process is
     unsuccessful.
     - Returns 0 to the child process
     */
    
    pid_t pid = fork();
    
    switch(pid)
    {
        case -1: // Failure as described above
            std::cout << "DEBUG:Fork Failure\n";
            exit(-1);
        case  0: // Child process - Parent will have a different value assigned
            
            //if(execvp(cmd_name, args) == -1)  // Run command, -1 denotes an error
        {
            std::cout << "Command Not Found\n"; // Notify user of error
            exit(0); //return to main loop
        }
            
        default:
            wait(NULL);
            std::cout << "DEBUG:Child Finished\n";
    }
}



// index is used as start point
void execute(char *** cmd, int length, int index) {
    int i = index;
    
    int pipes[2];
    
    
    
    // Place commands into a command array and keep track of length
    // We can then pass this to the run section to execute the commands.
    
    if (i <= length) { // For each command array
        cout <<"Direction: "<< cmd[i][1][0] <<endl;
        
        switch (cmd[i][1][0]) {
                
            case '|': { // Output to another process
                
                // Create pipe
                pipe(pipes);
                
                // Child process
                if (fork() == 0) {
                    // Replace standard input with input part of pipe
                    dup2(pipes[0], 0);
                    
                    // Close unused half
                    close(pipes[1]);
                    
                    // Execute next command
                    execute(cmd, length, index + 1);
                }
                else { // Parent process
                    
                    // replace standard output with output part of pipe
                    dup2(pipes[1], 1);
                    
                    // Close unused half
                    close(pipes[0]);
                    
                    // Execute current command
                    if(execvp(cmd[i][2], NULL) == -1)  // Run command, -1 denotes an error
                    {
                        std::cout << "Command Not Found\n"; // Notify user of error
                        exit(0); //return to main loop
                    }
                }
                
                break;
            }
                
            case '<': {// Read input from file
                
                // Open the input file ---- name = i + 1
                int in = open("scores", O_RDONLY);
                
                // Replace std in with file
                dup2(in, 0);
                
                // Close unused fd
                close(in);
                
                
                if (cmd[i + 1][1][0] == '|' || cmd[i + 1][1][0] == '>') {
                    
                    // Create pipe
                    pipe(pipes);
                    
                    // Child process
                    if (fork() == 0) {
                        // Replace standard input with input part of pipe
                        dup2(pipes[0], 0);
                        
                        // Close unused half
                        close(pipes[1]);
                        
                        // Execute next command
                        execute(cmd, length, index + 2);
                    }
                    else { // Parent process
                        
                        // replace standard output with output part of pipe
                        dup2(pipes[1], 1);
                        
                        // Close unused half
                        close(pipes[0]);
                        
                        // Execute current command
                        if(execvp(cmd[i][2], NULL) == -1)  // Run command, -1 denotes an error
                        {
                            std::cout << "Command Not Found\n"; // Notify user of error
                            exit(0); //return to main loop
                        }
                    }
                }
                else {
                    if(execvp(cmd[i][2], NULL) == -1)  // Run command, -1 denotes an error
                    {
                        std::cout << "Command Not Found\n"; // Notify user of error
                        exit(0); //return to main loop
                    }
                    
                }
                
                break;
            }
                
            case '>': {// Output to file
                
                // Open the output file ---- name = i + 1
                int out = open("test_out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                
                // replace standard output with output file
                dup2(out, 1);
                
                // Close unused fd
                close(out);
                
                // Execute command
                if(execvp(cmd[i][2], NULL) == -1)  // Run command, -1 denotes an error
                {
                    std::cout << "Command Not Found\n"; // Notify user of error
                    exit(0); //return to main loop
                }
                
                break;}
                
            default: {// Nothing is next so use std out file descriptor
                      // If we are not the first command, we are the last,
                      // so read from the last fd.
                if (i != 0)
                {
                    cout << "use prev fd"<<endl;
                }
                else
                {
                    // We are the first command so use std in.
                    cout << "std exe"<<endl;
                }
                break;}
        }
    }
    else {
        std::cout<< "END"<<endl;
    }
}






