#ifndef STRUCTS_H
# define STRUCTS_H

# include <aio.h>
# include <stdbool.h>

/*######################
#    File Descriptor   #
######################*/

typedef struct s_fd_node
{
	int					fd;
	struct s_fd_node	*next;
}	t_fd_node;

typedef struct s_fd_meta
{
	int			std_in;
	int			std_out;
	int			std_err;
	t_fd_node	*head;
	t_fd_node	*tail;
	size_t		size;
}	t_fd_meta;

/*######################
# Abstract Syntax Tree #
######################*/

typedef struct s_filedescriptor
{
	int	std_in;
	int	std_out;
	int	std_err;
}	t_filedescriptor;

typedef enum e_tree_node_type
{
	TEXT,
	PIPE,
	AND_IF,
	OR_IF,
	LESS,
	GREAT,
	DGREAT,
	DLESS,
	LPAREN,
	RPAREN
}	t_tree_node_type;

/*#############
# Redirection #
#############*/

typedef struct s_redirect_node
{
	t_tree_node_type		type;
	char					*file;
	struct s_redirect_node	*next;
}	t_redirect_node;

typedef struct s_redirection
{
	t_redirect_node	*head;
	t_redirect_node	*tail;
	unsigned int	size;
}	t_redirection;

/*######################
# Abstract Syntax Tree #
######################*/

typedef struct s_tree_node
{
	t_tree_node_type	type;
	char				**args;
	int					sub;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	t_redirection		redirect;
}	t_tree_node;

/*#########
# Parsing #
#########*/

typedef struct s_token
{
	char				**args;
	t_tree_node_type	type;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

/*###################
# Build Manager #
###################*/

typedef struct s_build_manager
{
	t_token			*head_token;
	t_token			*root_token;
	t_tree_node		*root_node;
}	t_build_manager;

/*#############
# Environment #
#############*/

typedef struct s_env_node
{
	char				*key;
	char				*value;
	unsigned int		key_len;
	unsigned int		value_len;
	struct s_env_node	*next;
	struct s_env_node	*prev;
}	t_env_node;

typedef struct s_environment
{
	t_env_node	*head;
	t_env_node	*tail;
	ssize_t		size;
}	t_environment;

/*###################
# Garbage Collector #
###################*/

typedef enum e_garbage_layers
{
	PERSISTENT,
	TEMPORARY
}	t_garbage_layers;

typedef struct s_garbage_node
{
	void					*mem;
	struct s_garbage_node	*next;
}	t_garbage_node;

typedef struct s_garbage_layer
{
	t_garbage_node	*head;
	t_garbage_node	*tail;
	ssize_t			size;
}	t_garbage_layer;

typedef struct s_garbage
{
	t_garbage_layer	persistent;
	t_garbage_layer	temporary;
}	t_garbage;

/*###########
# Minishell #
###########*/

typedef struct s_minishell
{
	t_tree_node			*tree_root;
	t_garbage			garbage;
	t_environment		env;
	t_filedescriptor	filedescriptor;
	bool				herdoc;
	int					last_exit_status;
	t_fd_meta			fd_table;
}	t_minishell;

/*###########
# Execution #
###########*/

typedef enum e_operator
{
	OP_AND,
	OP_OR
}	t_operator;

#endif