#include <iostream>
#include <windows.h>
#include <tchar.h>

void ParseArg(char * cmnd, char* cmd[], char input[])
{
	std::cout << "mywinshell> ";
	std::cin.getline(input, 50);
	cmnd = strtok(input, " ");
	int i = 0;

	while (cmnd != NULL) {
		cmd[i] = cmnd;
		i++;
		cmnd = strtok(NULL, " ");
	}
}


void Clean(char * cmd[]) {
	for (int a = 0; a < 40; a++) cmd[a] = NULL;
}


void Execute(char * cmd)
{
	// Create a process
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si)); // Write all data to zeros from starting point, for set distance
	si.cb = sizeof(si);          // Size of the structure - in bytes
	ZeroMemory(&pi, sizeof(pi)); // Write all data to zeros from starting point, for set distance

	// --- Check to see if the command is valid - ie exisits ---

	// Check to see if the command is a builtin
	// If builtin, run from bin folder
	// Else Check to see if it is a system command - run if is,
	// if not, return error message

	// Start the child process
	printf("Beginning New Process...\n");
	printf(cmd);
	printf("\n");
	//printf(argv[1]);
	if (!CreateProcess(NULL,
		cmd,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi)
		)
	{
		printf("Create Process failed (%d).\n", GetLastError());
		return;
	}
	printf("Running...\n");
	// Wait until child process exits
	// Do some more checking here to ensure that a deadlock doesn't occur - allow error messages to rise up
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	printf("End\n");
}


int main() 
{
	char * cmnd;
	char * cmd[40];
	char input[50];
	
	while (true)
	{
		Clean(cmd);
		ParseArg(cmd[0], cmd, input);
		int curr = 0;
		while (cmd[curr] != NULL) {
			if (strcmp(cmd[curr], "exit") == 0 || strcmp(cmd[curr], "quit") == 0) break;
			Execute(cmd[curr]);
			curr++;
		}
	}
	return 1; // Exit success
}