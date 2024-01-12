#include<stdio.h>
#include<errno.h> // error codes
#include<stdlib.h> // memory allocation
#include<string.h> // string ops on str
#include "../shell/shell.h" // prompt
#include "node.h" 
#include "../parser/parser.h" // AST generator

/*
* step1 : define new_node() function
        1- allocate memory dynamically for node
        2- set initial values of all struct attributes to 0
        3- set value of type to 'type' in argument
* step2 : define add_child_node()
        1- one case for when parent has no first child
        2- one case for when parent has first child
            i- when there is only one child
            ii- when there is more than one child (siblings already exist)
        3- increase children count
* step3 : define set_node_val_str()
        1- allocate memory for string
        2- create a copy of passed string (to avoid dependence on external string
* step4 : define free_node_tree()
        1- free(node)
        2- check if there are child nodes 
            i- call free_node_tree() recursively to free all successive nodes
            ii- return from recursion will be NULL; passed to the child node
        3- free the string pointer (if not already NULL)
*/

struct node_s *new_node(enum node_type_e *type){
    struct node_s *node = malloc(sizeof(struct node_s));

    if(!node){ // if node pointer NULL
        return NULL;
    }

    memset(node, 0, sizeof(struct node_s)); // pointer, value, dest. size
    node->type = type; // passed argument in func. is assigned to structure
    return node;
}

void add_child_node(struct node_s *parent, struct node_s *child){
    // incase parent or child are NULL
    if(!parent || !child){
        return NULL;
    }

    if(!parent->first_child){ // if no first child then, passed argument is the first child
        parent->first_child = child;
    }else{
        // possible that there already exists some siblings
        struct node_s *sibling = parent->first_child;

        while(sibling->next_sibling){ // as long as next_sibling is not NULL i.e there are siblings to the first_child
            sibling = sibling->next_sibling;
        }

        sibling->next_sibling = child;
        child->prev_sibling = sibling; // allocate prev_sibling pointer to the last child
    }
    parent->children++; // increase the count
}

void set_node_val_str(struct node_s *node, char *val){
    node->val_type = VAL_STR; // set value type for the node
    if(!val){
        node->val.str = NULL; 
    }else{
        char *val2 malloc(strlen(val)+1); //strlen won't count '\0'
        if(!val2){
            node->val.str = NULL;
        }else{
            strcpy(val2, val);
            node->val.str = val2; // this way str won't change with the OG string
        }
    }
}

void free_node_tree(struct node_s *node){ // selected node will be freed i.e memory allocated will be freed
    if(!node){
        return;
    }
    struct node_s *child = node->first_child; // prepare to move the target forward (for recursion)

    while(child){ // until any child to a node exists
        struct node_s *next = child->first_child; // prepare to move the target forward
        free_node_tree(next);
        child = next;
    }

    // free the string
    if(node->val_type = VAL_STR){
     if(node->val.str){
        free(node->free.str);
    }
    }

    free(node);
}
        
        
