#include <iostream>
#include <unistd.h>

#define STD_INPUT 0     // File descriptior for sandard input
#define STD_OUTPUT 1    // File descriptior for standard output
#define READ 0          // Read file descriptior from pipe
#define WRITE 1         // Write file descriptior from pipe


int main() {
    
 
    char *one[4]; // Command 1
    char *two[3]; // Commmand 2
    
    // list contents of /usr/lib
    one[0] = "ls";
    one[0] = "-l";
    one[2] = "/usr/lib";
    one[3] = (char *)0;
    
    two[0] = "grep";
    two[1] = "^d";
    two[2] = (char *)0;
    
    
    int p[2];
    
    pipe(p);  // check error here, p < 0...
    
    int pid;
    
    pid = fork(); // Switch here for fork results...
    
    // Catch errors here
    if (pid < 0){
         std::cout << "OH SNAP! Child failed" << std::endl;
         return -1;
     }
    
    if (pid == 0) { // We are in the child process - YAY
        std::cout << "Child" << std::endl;
        //std::cout << "Child is sending... " << std::endl;
        
        
        close(STD_OUTPUT);      // Close the standard output
        dup(p[WRITE]);       // Redirect standard output to pipe
        
        close(p[READ]);         // close file descriptors
        close(p[WRITE]);
        std::cout << "Child about to execute" << std::endl;
        execvp(one[0], one);  // Execute command 1
        // if return value, error occured....
        std::cout << "Child Done" << std::endl;
        exit(0);
        
        
        
        //if(execvp("ping", NULL) == -1)  // Run command -1 denotes an error
        //{
        //    std::cout << "Command Not Found" <<std::endl; // Notify user of error
        //     exit(0); //return to main loop
        // }

        //write(parent_to_child[1], &input, sizeof(char) * 40);
        
    
    } else { // We must be the parent
             //char output[40];
        
        std::cout << "Parent" << std::endl;
        //std::cout << "Waiting for child to send..." << std::endl;
       
        
        close(STD_OUTPUT);      // Close the standard output
        dup(p[READ]);          // Redirect standard input from pipe
        
        close(p[READ]);       // close file descriptors
        close(p[WRITE]);
        
        std::cout << "Parent about to execute" << std::endl;
        execvp(two[0], two);  // Execute command 2
        std::cout << "Parent Done" << std::endl;
        exit(0);
        
        
        //read(parent_to_child[0], &output, sizeof(char) * 40);
        
    }
    return 1;
}
