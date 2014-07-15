
#include "builtins.h"


/* Maybe have a list or data structure to store all of the builtin functions
 *
 */
bool is_builtin(char *input) {
    if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
        cout<< "Exit" <<endl;
        return true;
    }
    if (strcmp(cmd[0], "echo") == 0) {
        cout<< "Echo" <<endl;
        return true;
    }
    if (strcmp(cmd[0], "cd") == 0) {
        cout<< "Change Directory" <<endl;
        return true;
    }
    if (strcmp(cmd[0], "curr") == 0) {
        cout<< "Print Current Working Directory" <<endl;
        return true;
    }
    cout<< "Not builtin" <<endl;
    return false;
}

// Builtins to execute

// Exit
void exit() {
    // Do some quit code here...
}

// Echo
void echo(char ** cmd) {
    int i = 1;
    
    while (cmd[i] != NULL){
        std::cout << cmd[i] << " \n";
        i++;
    }
}


// Change Directory
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


// Print Current Directory
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
