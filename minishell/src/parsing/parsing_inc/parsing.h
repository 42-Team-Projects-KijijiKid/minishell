#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

t_token	*create_tokens(char *cmd);
void	parsing_process(char *cmd, t_meta *meta);


#endif