/*
//  token.h
//  
//
//  Created by Adam Sherlaw on 15/07/14.
//
*/

#ifndef ____token__
#define ____token__

#include <stdlib.h>
#include <string.h>


void malloc_operator(int index, char ** operators);
void new_array(int index, char *** cmd);
int tokenise(char * data, char *** command, char ** operators);

#endif /* defined(____token__) */
