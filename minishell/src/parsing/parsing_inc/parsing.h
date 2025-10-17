#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"
#include <stdbool.h>

typedef struct s_tmp_cmd_token
{
	char					*value;
	struct s_tmp_cmd_token	*next;
}	t_tmp_cmd_token;

void			parsing_process(char *cmd, t_meta *meta);
t_tmp_cmd_token	*create_tokens(char *cmd);


#endif