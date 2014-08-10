
#include "token.h"

#define SIZE 512


void new_array(int index, char *** cmd) {
    cmd[index] = (char **) malloc (sizeof(char *) * SIZE);
    cmd[index][0] = (char *) malloc (sizeof(char) * SIZE);
}


void malloc_operator(int index, char ** operators) {
    operators[index] = (char *) malloc (sizeof(char) * 10);
}


int tokenise(char * data, char *** command, char ** operators) {
    int insert_index = 0;
    int array_index = 0;
    
    /* Create a new array*/
    new_array(array_index, command);
    malloc_operator(array_index, operators);

    
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
                operators[array_index][0] = '<';
                
                new_array(++array_index, command);
                malloc_operator(array_index, operators);
                insert_index = 0;
                break;
                
            case '>':
                operators[array_index][0] = '>';
                
                new_array(++array_index, command);
                malloc_operator(array_index, operators);
                insert_index = 0;
                break;
                
            case '|':
                operators[array_index][0] = '|';

                new_array(++array_index, command);
                malloc_operator(array_index, operators);
                insert_index = 0;
                break;
                
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
        a = 0;
        split = strtok(command[i][0], " \n");
        
        while (split != NULL) {
            command[i][a] = (char *) malloc (sizeof(char) * 120);
            strcpy(command[i][a++], split);
            split = strtok(NULL, " \n");
        }
        operators[i][1] = a;
    }
    
    /* Clean the array to remove current elements */
    for (int i = 0; i < 20; i++) data[i] = (char)NULL;
    
    return array_index;
}
