#ifndef EXECUTE_H
# define EXECUTE_H

# include "redirects.h"
# include "builtins.h"

// execute_command.c
int		execute_command(t_tree_node *node);

// execute_operator.c
int		execute_and(t_tree_node *node);
int		execute_or(t_tree_node *node);

// execute_pipe.c
int		execute_pipe(t_tree_node *node);

// execute_subshell.c
int		execute_subshell(t_tree_node *node);

// execute.c
int		execute_node(t_tree_node *node);
int		execute_node_by_type(t_tree_node *node);
void	minishell_execute();

#endif
