#ifndef UTILS_H
# define UTILS_H

#include "structs.h"

// integrations/fti_malloc.c
void	*fti_malloc(ssize_t size, e_garbage_layers type);

// integrations/fti_readline.c
char	*fti_readline(char *promt);

// error.c
void	ft_error(char *msg, char *file, int line, u_int64_t exit_stat);

// garbage.c
void	garbage_free_all(void);

#endif
