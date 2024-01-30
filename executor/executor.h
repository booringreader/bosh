#ifndef BACKEND_H
#define BACKEND_H

#include "../node/node.h"

char *search_path(char *file); // takes the name of command and looks for executables in directories inside $PATH variable
int do_exec_cmd(int argc, char **argv); //executes a command
int do_simple_command(struct node_s *node); // main func. of executor

#endif
