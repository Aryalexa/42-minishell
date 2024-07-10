#ifndef BUILTIN_H
# define BUILTIN_H

#include "../2_structs/structs.h"
#include "../3_error/error.h"

void    exec_echo(t_cmdnode node, char *env[]);
void    expand_token_val(char *val);

#endif