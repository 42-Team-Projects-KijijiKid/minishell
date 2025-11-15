#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
//Malloc , pwd , cd, terminal information
#include <stdlib.h>
#include <unistd.h>
// Dir manipulation like read , close ,open
#include <sys/types.h>
#include <dirent.h>
// Strerror
#include <string.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../libft/libft.h"
#include "structs.h"
#include "execute/execute.h"
#include "parse/parse.h"
#include "environment.h"
#include "utils.h"

// Miishell
t_minishell	*minishell_initialize(char **env);
t_minishell	*minishell_get(void);

// error.c
void	ft_error(char *msg, char *file, int line, u_int64_t exit_stat);

// garbage.c
void	garbage_add_node(t_garbage_layer *garbage_layer, void *data);
void	garbage_add_to_layer(t_garbage_layer *garbage_layer, void *data);
void	garbage_free_layer(t_garbage_layer *garbage_layer);
void	garbage_free_all(void);

#endif