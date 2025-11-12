#ifndef EXECUTE_H
# define EXECUTE_H

# include "redirects.h"
# include "builtins.h"

// execute_command.c
void	execute_command(t_tree_node *node);

// execute_operator.c
void	execute_and(t_tree_node *node);
void	execute_or(t_tree_node *node);

// execute_pipe.c
void	execute_pipe(t_tree_node *node);

// execute_subshell.c
void	execute_subshell(t_tree_node *node);

// execute.c
void	execute_node(t_tree_node *node);
void	execute_node_by_type(t_tree_node *node);
void	minishell_execute();

#endif
