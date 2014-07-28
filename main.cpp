
#include "main.h"
#include "token.h"
#include "execution.h"

#include <unistd.h>
using namespace std;
/* Main structure:
 *      Continuous loop waiting for input
 *      When input is received, act accordingly
 */
int main() {
    char data[512];
    char *** cmd = (char ***)malloc(sizeof(char **) * 20);
    
    while(true) { // Infinate loop for now...
        int n = 0;
        int array_index = 0;
        
        // Read the input data
        // If no data, wait a set amount of time (say 1 second)
        //sleep(1);
        n = read(0, data, sizeof data);
        
        // Write data back out for debugging purposes
        //write(1, data, n);
        
        // Tokenise data - returns number of arrays in cmd
        array_index = tokenise(data, cmd);
        
        // Print for debugging
        for (int i = 0; i <= array_index; i++) {
            for (int j = 1; j < cmd[i][0][0]; j++) {
                cout<<"Output: "<< cmd[i][j] << endl;
            }
        }
        
        execute(cmd, array_index, 0);
    }
    
    exit(0);
}
