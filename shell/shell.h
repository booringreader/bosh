#ifndef SHELL_H
#define SHELL_H

char *read_cla(void);
void print_prompt1(void);
void print_prompt2(void);

#include "../source/source.h"
int parse_and_execute(struct source_s *src);
#endif
