#ifndef PARSER_H
#define PARSER_H

#include "../scanner/scanner.h" // struct token_s; to get token for generating AST
#include "../source/source.h" // struct source_s; to get input to generate tokens

// takes token structure as input and returns root node of the AST
struct node_s *parse_simple_command(struct token_s *tok);

#endif
