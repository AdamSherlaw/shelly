//
//  file_descriptors.cpp
//  
//
//  Created by Adam Sherlaw on 14/07/14.
//
//

#include "file_descriptors.h"
#include <unistd.h>

int main() {
    char buff[12];
    int n;
    
    while ((n = read(0, buff, sizeof buff)) > 0) {
        std::cout<<"N: " << n<<std::endl;
        write(1, buff, n);
    }
    exit(0);
}
