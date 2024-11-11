#ifndef SCANNER_H
#define SCANNER_H

/*
* step1 : create a structure of contain the tokens
*       1- link the structure that carries input
*       2- declare a pointer that tracks the token
*       3- declare a variable that keeps track of the length of the token (we won't have to call strlen() repeatedly)
* step2 : create a EOF token, that tracks the end of token
*       1- use extern to let the compiler know that the corresponding memory allocation will be in some other file
* step3 : create a tokenize function pointer (a function) of type token_s structure to read the next token
*/

// in C and C++ struct keyword is used everytime a structure is declared, defined, and used (possibly to differentiate it from func decs)

struct token_s{
    struct source_s *src;
    char *token_char; // keeps track of token characters
    int token_len; // keeps record of length of token; to avoid calling strlen()
};

extern struct token_s eof_token; // special EOF token, indicates end of input 

// function declaration to tokenize the next character from input
// retrieve the next token from the input
struct token_s *tokenize(struct source_s *src);
void free_token(struct token_s *tok); // helper function that takes pointer 'tok' as argument and returns nothing

#endif
