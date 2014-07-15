
#include "main.h"
#include "token.h"

#include <unistd.h>
using namespace std;
/* Main structure:
 *      Continuous loop waiting for input
 *      When input is received, act accordingly
 *          Input is from a file descriptor
 */
int main() {
    char data[512];
    char ** cmd = (char **)malloc(sizeof(char *) * 20); // Array of 20 char

    while(true) { // Infinate loop for now...
    /* Get input from fd
     * Tokenise and parse input
     * Run commands
     * Send output to fd.
     */
        int n = 0;
        int array_index = 0;
        
        // Clean out the commands from the array
        
        // Read the input data
        // If no data, wait a set amount of time (say 10 seconds)
        n = read(0, data, sizeof data);
        
        // Write data back out for debugging purposes
        std::cout<<"\n\nData: " << std::endl;
        write(1, data, n);
        
        // Tokenise data
        array_index = tokenise(data, cmd);
        
        
        // Print the arrays (for debugging)
        for (int i = 0; i <= array_index; i++) {
            for (int j = 2; j < strlen(cmd[i]); j++) {
                cout<< cmd[i][j] << endl;
            }
        }
    }
    
    exit(0);
}
