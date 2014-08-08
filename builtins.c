#include "builtins.h"

/* Change Directory */
void change_directory(char * directory) {
    char * current;     char * split;
    char ** temp;       char * next;
    long size;          int i = 0;
    
    if (strcmp(directory, "..") == 0) {
        size = pathconf(".", _PC_PATH_MAX);
        temp = (char **) malloc((size_t)size);
        directory = (char *) malloc((size_t)size);
        
        if ((current = (char *)malloc((size_t)size)) != NULL)
            getcwd(current, (size_t)size);
        
        split = strtok(current, "/");
        
        while (split != NULL) {
            temp[i] = (char *) malloc (sizeof(char) * 20);
            strcpy(temp[i], "/");
            strcat(temp[i++], split);
            split = strtok(NULL, "/");
        }
        
        for (int j = 0; j < i - 1; j++) strcat(directory, temp[j]);
        strcat(directory, "/");
    }
    
    if (chdir(directory) == -1) {
        printf("%s\n", "Given directory invalid\n");
        return;
    }
}
