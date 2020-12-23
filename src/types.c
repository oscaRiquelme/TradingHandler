#include<stdio.h>
#include "types.h"

void green(){
    printf("\033[0;32m");
}
void red(){
    printf("\033[0;31m");
}

void defaults(){
    printf("\033[0m"); 
}

void yellow(){
    printf("\033[0;33m");
}