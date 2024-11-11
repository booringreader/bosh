#ifndef NODE_H
#define NODE_H

/*
* step1 : declare and define enum to dictate the type of node pods (command and argument)
* step2 : declare and define enum to dictate the type of value stored in node pods 
* step3 : declare and define union to dictate the value stored in pods 
* step4 : bring together all of the above and define the structure of the nodes in AST
* step5 : declare the functions to operate on individual nodes (definition in .c file)
*/

enum node_type_e{ // defines the type of nodes we can store
    NODE_COMMAND, // root node of the command (represents the entire AST)
    NODE_VAR, // breaks down the command name and argument into child nodes
};

enum val_type_e{ // defines the type of values, we can store in a node
    VAL_SINT = 1, // signed int initialising the enum at 1
    VAL_UINT, // unsigned int
    VAL_SLLONG, // signed long long
    VAL_ULLONG, // unsigned long long
    VAL_FLOAT, // float
    VAL_LDOUBLE, // long double
    VAL_CHR, // charun
    VAL_STR, // string || char pointer ; for simple commands
};

union symval_u{ // symbol for value in union (each node can store only one type of value at a time)
    long                sint;
    unsigned long       uint;
    long long           sllong;
    unsigned long long  ullong;
    double              sfloat;
    long double         ldouble;
    char                chr;
    char                *str; // pointer to char
};

struct node_s {
    enum node_type_e type; // type of node pod
    enum val_type_e val_type; // type of value to be stored in this pod
    union symval_u val; // value stored in pod
    int children; // number of child nodes
    struct node_s *first_child; // pointer to a node pod i.e the first child
    struct node_s *prev_sibling, *next_sibling; // pointer to node pods which are prev and next siblings
};

struct node_s *new_node(enum node_type_e *type);
void add_child_node(struct node_s *parent, struct node_s *child);
void free_node_tree(struct node_s *node);
void set_node_val_str(struct node_s *node, char *val);

/*
* for simple commands(no arguments), the node attributes are following
* node_type_e : command (if root) or var (child)
* val_type : val_str 
* val.str : pointer to the string value
*/

#endif
