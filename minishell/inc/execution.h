#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"

char	**extract_path(char **envp);
char	*access_path(char *cmd, char **paths_2d);


#endif