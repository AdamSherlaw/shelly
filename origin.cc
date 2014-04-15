// Testing changes

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdlib.h>


using namespace std;

void ParseArg(char* cmnd, char* cmd[], char input[])
{
    
    cout << "myshell> ";
    cin.getline(input,50);
	cmnd = strtok(input, " ");
	int i = 0;
    
	while(cmnd != NULL)
	{
	    cmd[i] = cmnd;
	    i++;
	    cmnd = strtok(NULL, " ");
	}
}

void Clean(char* cmd[])
{
    //Clean Array
    for(int a=0; a < 40; a++)
    {
        cmd[a] = NULL;
    }
}

void Execute(char* cmd[])
{
    /* pid_t data type - Signed integer type which is capable of representing a
     process ID - In the GNU Lib this is an int.*/
    pid_t pid;
    pid = fork(); // fork() - create a copy of current process.
    switch(pid)
    {
        case -1:
            cout << "DEBUG:Fork Failure" << endl;
            exit(-1);
        case  0:
            execvp(cmd[0], cmd);
            
            if(execvp(cmd[0], cmd) == -1)
        {
            cout << "Command Not Found" << endl;
            exit(0);
        }
            
        default:
            wait(NULL);
            cout << "DEBUG:Child Finished" << endl;
    }
    
}
//cats
int main()
{
    char * cmnd;
    char begin;
    char * cmd[40];
    char input[50];
    
    char temp = 'X';
    cmd[0] = &temp;
    //cout << "begin!" << endl;
    
    while(cmd[0] != NULL)
    {
    	Clean(cmd);
        ParseArg(cmnd, cmd, input);
        if(strcmp(cmd[0], "exit") == 0 || strcmp(cmd[0], "quit") == 0 )
        {
            break;
        }
        else
        {
            Execute(cmd);
        }
        
    }
    
    return 1;
    
}