#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"


char	**extract_path(void);
char	*access_path(char *cmd, char **paths_2d);
void	execution_process(t_token *token);
int		ft_fork(void);

//I/O Redirections
void	run_cmd(t_token *token, t_redir_type redir_type, int fd);
void	out_redir(t_token *token);
void	in_redir(t_token *token);

#endif