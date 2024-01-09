#ifndef PARSER_H
#define PARSER_H

#include "../scanner/scanner.h" // struct token_s
#include "../source/source.h" // struct source_s

struct node_s *parse_simple_command(struct token_s *tok);

#endif
