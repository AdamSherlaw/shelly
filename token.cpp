
#include "token.h"
using namespace std;
#define SIZE 512


void new_array(int index, char id, char ** cmd) {
    cmd[index] = (char *) malloc (sizeof(char) * SIZE);
    cmd[index][0] = id;
    cmd[index][1] = ' ';
}


/*
 *
 */
int tokenise(char * data, char ** destination) {
    int insert_index = 2;
    int array_index = 0;

    
    // Create a new array set to zero by default
    new_array(array_index, 'n', destination);
    
    
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
            case '<':
                cout <<"Redirect <"<< endl;
                insert_index = 1;
                new_array(++array_index, '<', destination);
                break;
                
            case '>':
                cout <<"Redirect >"<< endl;
                insert_index = 1;
                new_array(++array_index, '>', destination);
                break;
                
            case '|':
                cout <<"Pipe |"<< endl;
                insert_index = 1;
                new_array(++array_index, '|', destination);
                break;
            case '\n':
                cout << "newline char" <<endl;
                break;
            case ';':
                cout<< "Semicolon Character"<<endl;
            default:
                destination[array_index][insert_index++] = data[i];
                break;
        }
    }
    
    // Clean the array
    for (int i = 0; i < 20; i++) data[i] = (char)NULL;
    return array_index;
}
