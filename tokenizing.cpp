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
    
    new_array(array_index, 'n');
    
    for (int i = 0; i <= array_index; i++) {
        for (int j = 0; j < strlen(cmd[i]); j++) {
            cout <<cmd[i][j] << j<< endl;
        }
    }
    
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
                    array_index++;
                    insert_index = 1;
                    new_array(array_index, '<');
                break;
                
                case '>':
                    cout <<"Redirect >"<< endl;
                    array_index++;
                    insert_index = 1;
                    new_array(array_index, '>');
                break;
                
                case '|':
                    cout <<"Pipe |"<< endl;
                    array_index++;
                    insert_index = 1;
                    new_array(array_index, '>');
                break;
                
            default: // Add elements to current array
                cmd[array_index][insert_index++] = data[i];
                break;
        }
    }
    
    // Print the cmd array
    for (int i = 0; i <= array_index; i++) {
        for (int j = 0; j < strlen(cmd[i]); j++) {
            cout <<cmd[i][j]<< endl;
        }
    }
    
    
    exit(0);
}



