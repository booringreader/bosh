#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include"../shell/shell.h" // has prompt definitions
#include"scanner.h"
#include"../source/source.h"  // has definition of struct source_s

/*
* step1 : declare variables to keep track of the token buffer (buffer refers to the memory block [generally array])
*       1- one pointer to track token char
*       2- one variable to track the bytes allocated to buffer; one variable to keep track of the index of buffer
* step2 : define the eof token 
* step3 : create a func. to add characters to buffer (it also needs to take care of buffer memory allocation)
* step4 : create a func. to convert strings to token (structure)
*       1- allocate memory for the token structure
*       2- fill other members of the structure
* step5 : func. to free memory occupied by token(structure & text)
* step6 : create a 'tokenize()' func. to control the process flow
*       1- allocate memory for token buffer
*       2- initialize all the pointers
*       3- call next_char() to retrieve next character from the input 
*        i) if the scanned next character is a whitespace, check the token buffer ; if the buffer is empty continue scanning i.e
*           skip the whitespace, else break out of the loop of scanning and proceed to next step
*        ii) if the scanned character is eof_token, exit function marking the end of input text
*       4- call the create_token() func. {step4} to convert the token buffer text to token 'structure'
*/

int tok_buffindex = -1;
int tok_buffsize = 0; // initially 
char *tok_buff = NULL;

struct token_s eof_token={
    .token_len = 0,
};

void add_to_buffer(char c){
    /*
    * pass in character c and add it to the next index
    * if the index exceeds buffer size, reallocate more memory
    *   apply exception handling on the allocation
    */
    tok_buff[tok_buffindex++] = c;

    if(tok_buffindex >= tok_buffsize){ 
        char *temp = realloc(tok_buff, tok_buffsize*2);

        if(!temp){
            errno = ENOMEM;
            return;
        }

        tok_buff = temp;
        tok_buffsize *= 2;
    }
}

// create_token takes a string as input and returns a token structure
// we take a string and put it inside a structre (after declaring and initialising it)

struct token_s *create_token(char *str){
    // create an empty token structure that can be returned after modification
    struct token_s *tok = malloc(sizeof(struct token_s));

    //exception handling
    if(!tok){
        return; 
    }
   
    memset(tok, 0, sizeof(struct token_s)); // sets all values of token members 0
    tok->token_len = strlen(str); 
    /*
    * inside structure tok
    *   text_len == strlen(str); *text = NULL; struct source = NULL;
    */

   // pointer to track the token (not structure but the actual token data)
    char *nstr = malloc(tok->token_len+1); 

    if(!nstr){
        free(tok);
        return;
        // if the token structure to-be is not initialised then no utility in occupying the memory block
    }

    // change the string str from contiguous storage to a format that is trackable (char by char)
    // nstr pointer facilitates tracking each character of the string str
    strcpy(nstr, str);
    tok->token_char = nstr; // text pointer tracking nstr

    return tok;
    // passes out tok->text, tok->text-len, the source_s struct is still uninitialized(it is there to hold pointer to input)
}

void free_token(struct token_s *tok){
    if(tok->token_char){
        free(tok->token_char); // free only the pointer to the token text;
    }
    free(tok); // free entire structure memory block
}

struct token_s *tokenize(struct source_s *src){
    /* 
    * flow :
    * use the function defined in source_s structure to retrieve next character
    * pass this character to the add_to_buff() function defined above, it takes care of creating a buff from the characters
    * next pass this to the create_token() func. to convert text into structure
    * occasionally use free_token();
    *----- note -----
    * 
    *allocate memory for the buffer -> initialize the buffer ->
    * call the function to scan characters from input -> build a string from those characters -> pass on to be create_token to be converted to structre (allocate memory for structure -> convert)
    */

    int endloop = 0; // keeps track of loop (when parser moves on to new word and repeats the process
    //implies to keep scanning forward
    if(!src || !src->buffer || !src->buffersize){ // validity of structure pointer, and pointers inside structure
        errno = ENODATA;
        return &eof_token;
    }

    if(!tok_buff){ //checks validity of text buffer
    // no memory allocated for the text buffer
        tok_buffsize = 1024;
        tok_buff = malloc(tok_buffsize);
        //if memory not allocated, then no mem available
        if(!tok_buff){
            errno=ENOMEM;
            return &eof_token; // since func returns a pointer
        }
    }

    tok_buffindex = 0; // update index form -1
    tok_buff[0] = '\0'; // initially empty text buffer

    // bring in input character
    char ch = next_char(src);

    // exception handling
    if(ch == ERRCHAR || ch == EOF){
       return &eof_token;
    }

    do{
        // handling all the possible characters incoming
        switch(ch){
            case ' ':
            case '\t':
                if(tok_buffindex > 0){ //i.e. there is already some of the input in the text buffer
                    endloop = 1;
                }
                break; // first token received; to-be processed furthur
            case '\n':
                if(tok_buffindex > 0){
                    // given that there is already a string to be tokenized in the text buffer, we can move forward without recording the next line char
                    unget_char(src);
                }else{
                    add_to_buffer(ch);
                }
                endloop = 1;
                break;
                
            default:
                add_to_buffer(ch);
                break; // breaks from switch block
        }

        if(endloop){
            break; // breaks from loop (do-while)
        }
    }while((ch=next_char(src)) != EOF); // ch = ... necessary to keep on iterating

    // case of no input except delimiting characters
    if(tok_buffindex == 0){
        return &eof_token;
    }

    //case of memory shortage
    if(tok_buffindex >= tok_buffsize){ // index (0-1023) >= size(1024)
       tok_buffindex--;
    } // why is this part necessary if add_to_buffer() takes care of allocating memory
    // the do-while loop adds the next character before checking for the EOF, 
    // i.e it will also add the EOF upon reaching the buff_size index; 
    //the corresponding symbol to mark the end of string is '\0'; hence tok_buffsize--

    tok_buff[tok_buffindex] = '\0';
    
    // token text string has been created; convert to structure
    struct token_s *tok = create_token(tok_buff);

    //error handling incase tok is not assigned; memory buffer must've been corrupt
    if(!tok){
    fprintf(stderr, "failed to allocate buffer - %s\n", strerror(errno));
    return &eof_token;
    }
    tok->src = src;
    return tok;
}
