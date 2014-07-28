// Array index may need to be stored as a global to be used for number of
// commands to run

#include "tokenizing.h"
#include <string.h>
#include <unistd.h>
#include "token.h"
using namespace std;

char *** cmd = (char ***)malloc(sizeof(char **) * 20); // Array of 20 char pointers


int main() {
    // Input is limited to 512 characters at the moment... We may want to
    // increase this if we feel that it is necessary.
    char data[512];
    int insert_index = 2;
    int array_index = 0;

    read(0, data, sizeof data);
    
    std::cout<<"\n\nData: " << std::endl;
    write(1, data, n);
    
    tokenise(data, cmd);
    
    // Print the arrays
    for (int i = 0; i <= array_index; i++) {
        for (int j = 2; j < strlen(cmd[i]); j++) {
            cout <<cmd[i][j]<< endl;
        }
    }
    
    
    // ---------------  Begin parsing user input tokens.  --------------- //
    char * tmp;
    
    /* First element after spit is the character to define the redirection type
     * Second element is the command name to be executed
     * Third until end is the arguments that go along with the executed command.
     */
    
   
    
    // Iterate over each array, then over each array element
    for (int i = 0; i <= array_index; i++) {
        tmp = strtok(cmd[i], " ");  // Split string into tokens by white space
        
        bool first = true; // Used to remove the first element in the array
        while (tmp != NULL) {
            cout << tmp <<endl;
            if (!first) is_builtin(tmp);
            else first = false;
            // ----- Store tmp in another array to be used for execution ------
            tmp = strtok(NULL, " ");
        }
    }
    
    exit(0);
}



