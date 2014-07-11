
#include <unistd.h>
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

//#include "pipe.h"


bool builtin = false;       // Is the command a builtin?


void parseArg(char **cmd) {
    int i = 0;
    char input[120]; // To store input
    char * cmnd;
    
    
    std::cout << "Shelly> ";   // Prompt output
    std::cin.getline(input, 120); // Get input from user
	cmnd = strtok(input, " ");  // Split string into tokens by white space
	
    // Iterate over cmnd tokens and store them in the cmd array
	while(cmnd != NULL) {
        cmd[i] = (char *) malloc (sizeof(char) * 120);
        strcpy(cmd[i], cmnd);
        i++;
	    cmnd = strtok(NULL, " "); // resplit the string - when empty, return == NULL
	}
}



void clean(char * cmd[]) {
    // Clean the array out of any previous commands
    for(int a = 0; a < 20; a++) cmd[a] = (char *)NULL;
}



void Execute(char* cmd[])
{
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
            
            if(execvp(cmd[0], cmd) == -1)  // Run command, -1 denotes an error
            {
                std::cout << "Command Not Found\n"; // Notify user of error
                exit(0); //return to main loop
            }
            
        default:
            wait(NULL);
            std::cout << "DEBUG:Child Finished\n";
    }
    // if there is a pipe between the current command and the next
}



void remove_element(char ** array, int index, int size) {
    std::cout << "Debug: remove_element : begin\n";
    std::cout << "Deleting : " << array[index] << "\n";
    
    for (int i = index; i <= size; i++) {
        if (i != size) strcpy(array[i], array[i + 1]);
        else array[i] = (char *)NULL;
    }
    std::cout << "Debug: remove_element : end\n";
}


char * current_working_directory() {
    long size;
    char *buf;
    char *cwd;
    
    size = pathconf(".", _PC_PATH_MAX); // returns the maximum length of a relative pathname when path or filedes is the current working directory
    
    if ((buf = (char *)malloc((size_t)size)) != NULL) {
        cwd = getcwd(buf, (size_t)size);
        
        std::cout << cwd << "\n";
        return cwd;
    }
    return NULL;
}


void change_directory (char ** cmd) {
    char *directory = "/tmp";
    int ret;
    
    if (cmd[1] != NULL) { // If NULL, do nothing
        if (strcmp(cmd[1], "..") == 0) {        // If 2 dots, go back by one directory
            
            // Split the end off of the current directory
            // directory = ...
            std::cout << "You are still in : " << std::endl;
            char * cwd = current_working_directory();
            //char * result;
            
            cwd = strtok(cwd, "/");
            
            // Split into directories, and remove the last dir
            /*while (cwd!= NULL) {
                strcpy(result, cwd);
                cwd = strtok(NULL, "/");
            }*/
            
            //std::cout << cwd << "\n";
            
            // Remove commands from the list once completed
            
            //int array_size = (int)(sizeof(&cmd)/sizeof(*cmd));
            //remove_element(cmd, 0, array_size--);
            //remove_element(cmd, 0, array_size--);
            //std::cout << "element removed\n";
            
        } else {
            std::cout << "something else given!\n";
            directory = cmd[1];
        }
    }
    ret = chdir (directory);
}


void echo(char ** cmd) {
    int i = 1;
    
    while (cmd[i] != NULL){
       std::cout << cmd[i] << " \n";
       i++;
    }
}

int main() {
    char ** cmd = (char **)malloc(sizeof(char *) * 20); // Array of 20 char pointers
   
    while(true) {    //cmd[0] != NULL
        clean(cmd);
        parseArg(cmd); // Get input
        
        // Add to history here
        
        // Check for exit commands - these are builtins...
        if (strcmp(cmd[0], "exit") == 0 || strcmp(cmd[0], "quit") == 0 ) break;
        
        
        // Piping
        if (cmd[1] != NULL && cmd[2] != NULL) {
            if (strcmp(cmd[1], " | ")) {
                piping(cmd[0], cmd[2]);
                builtin = true;
            }
        }
        
        // Print current directory
        if (strcmp(cmd[0], "curr") == 0) {
            current_working_directory();
            builtin = true;
        }
        
        // Change directory
        if (strcmp(cmd[0], "cd") == 0) {
            change_directory(cmd);
            builtin = true;
        }
        
        // Echo input
        if (strcmp(cmd[0], "echo") == 0) {
            echo(cmd);
            builtin = true;
        }
        
        // If command is an OS built in.
        if (!builtin) {
            Execute(cmd); // run commands
        }
    }
    return 1; // exit success
}





