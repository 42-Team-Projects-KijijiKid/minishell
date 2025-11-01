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
#include "token.h"
#include "libft.h"
#include "garbage.h"
#include "execution.h"
#include "parsing.h"

typedef struct	s_meta
{
	t_token		*head;
	t_garbage	garbage;
	t_env_meta	env;
}	t_meta;

///Util Prototypes

//	utils
t_meta	*init_meta(char **envp);
t_meta	*get_meta(void);
//	error
void	*ft_malloc(ssize_t size, t_layer_type type);
void	ft_error(char *msg, char *file, int line, u_int64_t exit_stat);


#endif