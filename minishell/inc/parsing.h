#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

typedef struct s_tmp_cmd_token
{
	char					**args_2d;
	struct s_tmp_cmd_token	*next;
	struct s_tmp_cmd_token	*prev;
}	t_tmp_cmd_token;

void			parsing_process(char *cmd);
t_tmp_cmd_token	*create_commands(char *cmd);
void			expand_tokens(t_token *head);
char			*rtn_str_quotes(char **str);

char	**special_split(char **str);

//Token Gen
t_token	*create_tokens(t_tmp_cmd_token *cmd_head);
char	**give_2d_arg(char **str);
bool	is_meta_char(char cmd);
char	*str_in_quotes(char **str);

//Parsing functions
t_token	*find_root(t_token *token_head);
t_token	*find_root_reversed(t_token *token_head);
void	build_ast(t_token *root);

//Debug Functions
void	print_tokens(t_token *token);
void	print_ast_structure(t_token *root, int level, bool left);

//Syntax
void	check_quotes(char *line);

//Redirection
void	set_redirections(t_token *token_head);
void	handle_pipe(t_token *head_token);
void	handle_append(t_token *head_token);
void	handle_heredoc(t_token *head_token);
void	handle_io_redir(t_token *head_token);


#endif