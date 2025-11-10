#ifndef UTILS_H
# define UTILS_H

#include "structs.h"

// integrations/fti_malloc.c
void	*fti_malloc(ssize_t size, e_garbage_layers type);

// integrations/fti_readline.c
char	*fti_readline(char *promt);

#endif
