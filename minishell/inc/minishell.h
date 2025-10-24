#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "token.h"
#include "libft.h"
#include "garbage.h"
//Malloc , pwd , cd, terminal information
#include <stdlib.h>
#include <unistd.h>
// Dir manipulation like read , close ,open
#include <sys/types.h>
#include <dirent.h>
// Strerror
#include <string.h>

#include <termios.h>



typedef struct	s_meta
{
	t_token		*head;
	t_mem_block	*layer_1;
	t_mem_block	*layer_2;
	t_mem_block	*layer_3;
}	t_meta;


#endif
