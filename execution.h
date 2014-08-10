/*
//  execution.h
//  
//
//  Created by Adam Sherlaw on 15/07/14.
//
*/

#ifndef ____execution__
#define ____execution__

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "builtins.h"


void execute(char ** cmd);
void pre_execute(char ** cmd, char ** operators, int length, int index);

#endif
