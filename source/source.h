#ifndef SOURCE_H
#define SOURCE_H

#define EOF (-1)
#define ERRCHAR (0)

#define INIT_SRC_POS (-2)

// passing input data to the scanner directly from the buffer is easy, but
// it will create complexities when manipulating the pointers to individual characters
// hence we use a structure abstract the input data and some position pointers 
struct source_s{ 
    char *buffer; //input text

    // ? two 'long' strings to store info about the string's length &
    // ? our curren position in the string (where the next character will be taken from)
    long buffersize; //size of the input text
    long currentpos;  //absolute position in the source
};

//to retrieve the next character from the input
char next_char(struct source_s *src);

//to return the previously read character to the input i.e mark it as unread
void unget_char(struct source_s *src);

/*
* to look at the next character in the input without retrieving it i.e the pointer tracking the current location is the same position but can still feed the scanner with the next input character
*/
char peek_char(struct source_s *src);

// skip white spaces
void skip_white_spaces(struct source_s *src);

#endif
