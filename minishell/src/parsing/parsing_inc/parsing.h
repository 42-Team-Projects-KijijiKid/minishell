#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"
#include <stdbool.h>

typedef struct s_tmp_cmd_token
{
	char					*value;
	char					**args_2d;
	struct s_tmp_cmd_token	*next;
	struct s_tmp_cmd_token	*prev;
}	t_tmp_cmd_token;

void			parsing_process(char *cmd, t_meta *meta);
t_tmp_cmd_token	*create_commands(char *cmd);


//Token Gen
t_token	*create_tokens(t_tmp_cmd_token *cmd_head);
char	**give_2d_arg(char **str);
bool	is_meta_char(char cmd);

//Parsing functions
t_token	*find_root(t_token *token_head);
t_token	*find_root_reversed(t_token *token_head);
void	build_ast(t_token *root);

//Debug Functions
void	print_tokens(t_token *token);
void print_ast_structure(t_token *root, int level);



#endif