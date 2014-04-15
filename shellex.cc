
#include <unistd.h>
#include <iostream>


void ParseArg(char* cmnd, char* cmd[], char input[])
{
    std::cout << "myshell> "; // Prompt output
    std::cin.getline(input,50); // Get input from user - store in input var, 50 ch max
	cmnd = strtok(input, " "); // Split string into tokens by white space
	int i = 0;
    
    // Iterate over cmnd tokens and store them in the cmd array
	while(cmnd != NULL)
	{
	    cmd[i] = cmnd; // Take current command, put in array - ie ls -l = 2 cmds
	    i++;
	    cmnd = strtok(NULL, " "); // resplit the string - when empty == NULL
	}
}

void Clean(char * cmd[])
{
    // Clean the array out of any previous commands
    for(int a = 0; a < 40; a++) cmd[a] = NULL;
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
    pid_t pid;
    pid = fork();
    switch(pid)
    {
        case -1: // Failure as described above
            std::cout << "DEBUG:Fork Failure" <<std::endl;
            exit(-1);
        case  0: // Child process - Parent will have a different value assigned
            
            if(execvp(cmd[0], cmd) == -1)  // Run command -1 denotes an error
        {
            std::cout << "Command Not Found" <<std::endl; // Notify user of error
            exit(0); //return to main loop
        }
            
        default:
            wait(NULL);
            std::cout << "DEBUG:Child Finished" <<std::endl;
    }
}


int main()
{
    char * cmnd; // To store tokenised input - broken up by white space
    char begin;
    char * cmd[40];
    char input[50]; // To store input
    
    char temp = 'X';
    cmd[0] = &temp;
    
    while(cmd[0] != NULL)
    {
    	Clean(cmd); // Clean array
        ParseArg(cmnd, cmd, input); // Get input
        // check for exit commands - these are builtins...
        if(strcmp(cmd[0], "exit") == 0 || strcmp(cmd[0], "quit") == 0 ) break;
        
        Execute(cmd); // run commands
    }
    
    return 1; // exit success
    
}