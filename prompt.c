#include<stdio.h>
#include "shell/shell.h"

void print_prompt1(){
    fprintf(stderr, "$ ");
    }

void print_prompt2(void){
    fprintf(stderr, "> ");
    }
