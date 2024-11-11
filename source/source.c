#include "../shell/shell.h"
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

char next_char(struct source_s *src){
    // if there is no input
    if(!src || !src->buffer){
        errno = ENODATA; // ENODATA is an error code in errno.h
        return ERRCHAR; //return 0;
    }
   
   char c1 = 0; // will be used to store value when currentpos at some random point
    // when currentpos is at the very beginning i.e. at INTI_SRC_POS
    if(src->currentpos == INIT_SRC_POS){
        src->currentpos = -1;
    }else{ 
    // when currentpos is at some arbitrary character of input string
        c1 = src->buffer[src->currentpos];
    }
    // when currentpos is at the very end of input string i.e last character
    if(++src->currentpos >= src->buffersize){
        src->currentpos = src->buffersize;
        return EOF; // end of input string
    }

    return src->buffer[src->currentpos];
}

void unget_char(struct source_s *src){
    /*
    * step1 : move the position tracking pointer (ptp) to the previous index
    * step2 : dealing with any error in input 
    *       1- no input available
    *       2- input available but ptp not at a valid index
    */
    if(src->currentpos < 0){
        return;
    }
    src->currentpos--;
}

char peek_char(struct source_s *src){
    /* 
    * step1 : make a variable to store the index of next character
    * step2 : return the buffer[] of the next character
    * step3 : begin dealing with corner cases and exceptions
    *       1- when the input string is empty
    *       2- when input string at INIT_SRC_POS (input exists)
    *       3- when next character is more or equal to buffersize i.e null
    */
    if(!src || !src->buffer){
        errno = ENODATA;
        return ERRCHAR;
    }
    
    long pos = src->currentpos;

    if(pos == INIT_SRC_POS){
        pos++;  // return all at the end
    }
    
    pos++; // no utility in using else since this would be the only other case

    if(pos >= src->buffersize){
        return EOF; // returns the char 'EOF' which will be replaced by -1 during preprocessing. this 'EOF' is not the one used during file handling
    }
    return src->buffer[pos];
}

void skip_white_spaces(struct source_s *src){
    /*
    * step1 : check if the input exists
    * step2 : check for the next character being eof
    * step3 : check for the next character being " " || "\t"
    */
    if(!src || !src->buffer){
        return;
    }
    char c; // to store peeked value (step2)

    if((c=peek_char(src) != EOF) && c==" " || c=="\t"){
        next_char(src); // shifts the position tracking pointer to next index and returns its value
    }
}
