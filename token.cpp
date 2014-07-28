
#include "token.h"
using namespace std;
#define SIZE 512


void new_array(int index, char *** cmd) {
    cmd[index] = (char **) malloc (sizeof(char *) * SIZE);
    cmd[index][0] = (char *) malloc (sizeof(char) * SIZE);
    cmd[index][0][0] = 'n';
    cmd[index][0][1] = ' ';
}


int tokenise(char * data, char *** command) {
    int insert_index = 2;
    int array_index = 0;
    
    
    // Create a new array set to zero by default
    new_array(array_index, command);
    
    
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
                //cout <<"Redirect <"<< endl;
                insert_index = 1;
                command[array_index][0][0] = '<';
                new_array(++array_index, command);
                break;
                
            case '>':
                //cout <<"Redirect >"<< endl;
                insert_index = 1;
                command[array_index][0][0] = '>';
                new_array(++array_index, command);
                break;
                
            case '|':
                //cout <<"Pipe |"<< endl;
                insert_index = 1;
                command[array_index][0][0] = '|';
                new_array(++array_index, command);
                break;
            case '\n':
                //cout << "newline char" <<endl;
                break;
            case ';':
                //cout<< "Semicolon Character"<<endl;
            default:
                command[array_index][0][insert_index++] = data[i];
                break;
        }
    }
    
    
    /*  For each of the pre split arrays
     Split the data by white space.
     Store each 'word / command in a new array'
     */
    char * split;
    int a;
    
    
    
    for (int i = 0; i <= array_index; i++) {
        a = 1;
        split = strtok(command[i][0], " ");
        
        while(split != NULL) {
            command[i][a] = (char *) malloc (sizeof(char) * 120);
            //cout<<split<<endl;
            strcpy(command[i][a++], split);
            split = strtok(NULL, " ");
        }
        // Set the first element in the first array to the number of elements
        // in the array.
        command[i][0][0] = a;
    }
    
    // Print for debugging
    /*for (int i = 0; i <= array_index; i++) {
     for (int j = 1; j < command[i][0][0]; j++) {
     cout<<"Output: "<< command[i][j] << endl;
     }
     }*/
    
    // Clean the array to remove current elements
    for (int i = 0; i < 20; i++) data[i] = (char)NULL;
    
    return array_index;
}





