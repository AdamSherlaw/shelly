#include "tokenizing.h"
#include <string.h>
using namespace std;

#define SIZE 120
char ** cmd = (char **)malloc(sizeof(char *) * 20); // Array of 20 char pointers

void new_array(int index, char id) {
    cmd[index] = (char *) malloc (sizeof(char) * SIZE);
    cmd[index][0] = id;
}


int main() {
    char data[30];
    int insert_index = 1;
    int array_index = 0;
    
    cout << "Prompt>> ";
    std::cin.getline(data, 120); // Get input from user
    
    cout <<"Tokenizing: "<< data << endl;
    
    // Create a new array set to zero by default
    new_array(array_index, 'n');
    
    
    /* This switch block is used to parse the user input.
     * The input is broken up and stored in arrays. This allows us to
     * execute commands and their associated command line arguments.
     *
     * When a pipe or redirection character is encountered, a new array is
     * created. E.G. 
     *              Input: cmd1 args1 args2 args3 | cmd2 args4 args5
     *              Tokenized Ouptut: 
     *                               Array1: cmd1 args1 args2 args3
     *                               Array2: cmd2 args4 args5
     *
     * This gives us an easy to use tokenizer for piping and redirection.
     * The first element in each array tells us what type of operator is used
     * between the two blocks. 
     *
     * 'n' denotes a single block with no redirection or piping
     * '|' denotes a pipe
     * '<' denotes a lefthand redirect
     * '>' denotes a righthand redirect
     */
    for (int i = 0; i < strlen(data); i++) {
        switch (data[i]) {
                //case ' ':
                /* Everything before first space is the command name / location
                   if (first_space not found / taken)
                        this is the first command
                        Every thing after (up to the redirections piping chars)
                        Or the end of input are arguments for the first command.
                 */
                //if (!space) {
                //    cout <<"First space"<< endl;
                    /* Copy from beginning of array to current position to get
                       command
                     */
                //}
                //break;
                
                case '<':
                    cout <<"Redirect <"<< endl;
                    insert_index = 1;
                    new_array(++array_index, '<');
                break;
                
                case '>':
                    cout <<"Redirect >"<< endl;
                    insert_index = 1;
                    new_array(++array_index, '>');
                break;
                
                case '|':
                    cout <<"Pipe |"<< endl;
                    insert_index = 1;
                    new_array(++array_index, '|');
                break;
                
                default:
                    cmd[array_index][insert_index++] = data[i];
                break;
        }
    }
    
    // Print the arrays
    for (int i = 0; i <= array_index; i++) {
        for (int j = 0; j < strlen(cmd[i]); j++) {
            cout <<cmd[i][j]<< endl;
        }
    }
    
    
    exit(0);
}



