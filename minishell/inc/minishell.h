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
#include "parsing.h"
#include "garbage.h"
#include "execution.h"

/// @brief A node for storing the
/// environment variables in a linked list.
/// In the key value format.
typedef	struct s_env_node
{
	char				*key;
	char				*value;
	unsigned int		key_len;
	unsigned int		value_len;
	struct s_env_node	*next;
	struct s_env_node	*prev;
}	t_env_node;

/// @brief Meta Node for the 
/// linked list storing the
/// environment variables
/// in a linked list of key and values.
/// The storing upside down (eg.
/// accessing the first element 
/// is done via dereferencing the head)
typedef struct s_env_meta
{
	t_env_node	*head;
	t_env_node	*tail;
	ssize_t		size;
}	t_env_meta;

typedef struct	s_meta
{
	t_token		*head;
	t_garbage	garbage;
	t_env_meta	env;
}	t_meta;

//	utils
t_meta	*init_meta(char **envp);
t_meta	*get_meta(void);
int		ft_open(char *filename, int oflag);
//	error
void	*ft_malloc(ssize_t size, t_layer_type type);
void	ft_error(char *msg, char *file, int line, u_int64_t exit_stat);


#endif