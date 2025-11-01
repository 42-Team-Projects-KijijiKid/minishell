#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

/// @brief A node for storing the
/// environment variables in a linked list.
/// In the key value format.
typedef	struct s_env_node
{
	char				*key;
	char				*value;
	unsigned int		key_len;
	unsigned int		value_len;
	struct s_env_node	*next;
	struct s_env_node	*prev;
}	t_env_node;

/// @brief Meta Node for the 
/// linked list storing the
/// environment variables
/// in a linked list of key and values
typedef struct s_env_meta
{
	t_env_node	*head;
	t_env_node	*tail;
	ssize_t		size;
}	t_env_meta;

/// @brief Temporary token
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

char			**special_split(char **str);

//Token Gen
t_token			*create_tokens(t_tmp_cmd_token *cmd_head);
char			**give_2d_arg(char **str);
bool			is_meta_char(char cmd);
char			*str_in_quotes(char **str);
int				word_count(char *str);

//Parsing functions
t_token			*find_root(t_token *token_head);
t_token			*find_root_reversed(t_token *token_head);
void			build_ast(t_token *root);

//Expansion
void			expand_process(t_token *token);
char			*expand_inside_str(char *str, char quote);
int				strlen_whitout_quotes(char *str, char quote);

//Debug Functions
void			print_tokens(t_token *token);
void			print_ast_structure(t_token *root, int level, bool left);

//Syntax
void			check_syntax(char *line);

//Redirection
void			assign_redir_node_values(t_token *token, t_redir_type redir_type, int fd);
void			set_redirections(t_token *token_head);
void			handle_pipe(t_token *token);
void			handle_append(t_token *token);
void			handle_heredoc(t_token *token);
void			handle_io_redir(t_token *token);
void			set_node_val(t_redir *node);

//Create Env
void			parse_env(char **envp);

//Readline
char			*ft_readline(char *promt);

#endif