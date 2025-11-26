#ifndef EXECUTE_H
# define EXECUTE_H

# include "redirects.h"
# include "builtins.h"

// filedescripor_helpers.c
void	default_filedescripor(void);
void	close_default_filedescriptor(void);
void	add_fd_to_list(int fd);

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
void	minishell_execute(void);

//execute_helpers.c
char	*get_bin_path_of_command(char *cmd, char **paths_2d);
char	**get_path_array(char **envp);

#endif