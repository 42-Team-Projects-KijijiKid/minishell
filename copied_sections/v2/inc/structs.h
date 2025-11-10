#ifndef STRUCTS_H
# define STRUCTS_H

# include <aio.h> // for ssize_t

/*######################
# Abstract Syntax Tree #
######################*/

typedef enum	e_tree_node_type
{
	T_TEXT,
	T_PIPE,
	T_AND,
	T_OR,
	T_IN_RDR,
	T_OUT_RDR,
	T_APPEND,
	T_HEREDOC
}	e_tree_node_type;

typedef struct s_tree_node
{
	e_tree_node_type	type;
	char				**cmd_args;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

/*#############
# Environment #
#############*/

typedef struct	s_env_node
{
	char						*key;
	char						*value;
	unsigned int				key_len;
	unsigned int				value_len;
	struct s_env_node	*next;
	struct s_env_node	*prev;
}	t_env_node;

typedef struct	s_environment
{
	t_env_node	*head;
	t_env_node	*tail;
	ssize_t		size;
}	t_environment;

/*###################
# Garbage Collector #
###################*/

typedef enum	e_garbage_layers
{
	PERSISTENT,
	TEMPORARY
}	e_garbage_layers;

typedef struct s_garbage_node
{
	void				*mem;
	struct	s_garbage_node	*next;
}	t_garbage_node;

typedef struct s_garbage_layer
{
	t_garbage_node	*head;
	t_garbage_node	*tail;
	ssize_t		size;
}	t_garbage_layer;

typedef struct s_garbage
{
	t_garbage_layer	persistent;
	t_garbage_layer	temporary;
}	t_garbage;

/*###########
# Minishell #
###########*/

typedef struct	s_minishell
{
	t_tree_node		*head;
	t_garbage		garbage;
	t_environment	env;
}	t_minishell;

#endif