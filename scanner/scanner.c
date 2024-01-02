#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include"../shell/shell.h" // has prompt definitions
#include"scanner.h"
#include"../source.h"  // has definition of struct source_s

/*
* step1 : declare variables to keep track of the token buffer (buffer refers to the memory block [generally array])
*       1- one pointer to track token char
*       2- one variable to track the bytes allocated to buffer; one variable to keep track of the index of buffer
* step2 : define the eof token 
* step3 : create a func. to add characters to buffer (it also needs to take care of buffer memory allocation)
* step4 : 
