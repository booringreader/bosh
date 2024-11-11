#include "../source/source.h" // source_s as ...
#include "../scanner/scanner.h" // token_s as input argument
#include <unistd.h>
#include "../node/node.h" // contains node definition
#include "parser.h" // contains definition of parser function
#include "../shell/shell.h" // (?)

/*
* step1 : to define a function that takes token as input and gives AST node as output
*       1- check whether the passed token is not garbage; if it is, not point in making a AST (abstract syntax tree)
* step2 : create a new node head
*/

struct node_s *parse_simple_command(struct token_s *tok){
    if(!tok){
        return NULL;
    }
    struct node_s *cmd = new_node(NODE_COMMAND); // creates a root node (stores pointers to all info about the input i.e command and arguments)

    // if the root node is garbage, remove the respective token from AST conversion list
    if(!cmd){
        free_token(tok);
        return NULL;
    }

    struct source_s *src = tok->src; // (for the sake of modularity we will use the following loop to assign tokenizable text to the function instead of letting the function itself choose the source src)

    do{
        if(tok->token_char[0] = '\n'){ // first character in the token is new line
            free_token(tok);
            break; // if the token is new line, we don't need to do anything with it except move on to the next one
        }

        // the root node is formed, time to segment it into child(coommand) and siblings (arguments)
        struct node_s *word = new_node(NODE_VAR);

        if(!word){
            free_node_tree(cmd); // (?)
            free_token(tok);
            return NULL;
        }
        set_nod_value_str(word, tok->token_char); // give the node some value
        add_child_node(cmd, word);

        free_token(tok); // token added to the tree; free it and move to next one
        // supposed to free the text if any, so that the pointer moves to the next word from the input 
    }while((tok = tokenize(src)) != &eof_token);

    // when the entire toke i.e one line of input ends (eof_token)
    // return the entire corresponding AST

    return cmd;
}
