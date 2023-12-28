#ifndef SOURCE_H
#define SOURCE_H

#define EOF (-1)
#define ERRCHAR (0)

#define INIT_SRC_POS (-2)

struct source_s{
    char *buffer; //input text
    long buffersize; //size of the input text
    long currentpos;  //absolute position in the source
};

char next_char(struct source_s *src);
void retrn_char(struct source_s *src);
char peek_char(struct source_s *src);
void skip_white(struct source_s *src);

#endif
