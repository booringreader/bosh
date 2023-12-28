#include "shell.h"
#include "source.h"
#include<errno.h>

/*
*following function takes a pointer of type 'struct source_s' as input and 
*gives out a character as output.
*first we need to make sure the pointer is pointing towards something and is not NULL
*the first condition in the first code block cushions the fall in case there was some
*error while making the structure source_s; the second condition makes sure that the 
*pointer(named buffer) is pointing towards a character from input text or not.
*
*ENODATA is the macro used that signifies: no input is available on the STREAM
*ERRCHAR is a token defined in source header file.
*/
char retrn_char(struct source_s *src){
   if(!src || !src->buffer){
    errno = ENODATA;
    return ERRCHAR;
    }


}
