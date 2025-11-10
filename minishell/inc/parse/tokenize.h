#ifndef TOKENIZE_H
# define TOKENIZE_H

#include "../structs.h"

// token_list_utils.c
t_token	*get_last_node(t_token *head);
bool	is_redirect(e_tree_node_type type);
t_token	*get_left_tokens(t_token **root);
t_token	*get_right_tokens(t_token **root);

// tokenization_utils.c
int		calculate_word_length(char *str);
int		get_quoted_string_len(char *str);

// tokenize_command.c
char	*extract_quoted_string(char **str);
char	*extract_unquoted_string(char **str);
char	*extract_next_token(char **str);
char	**tokenize_command(char **str);

// tokenize_operator.c
char	**tokenize_operator(char **str);

// tokens_process.c
t_token	*tokens_process(t_token *head_token);

// tokens_seperate.c
bool	is_meta_char(char cmd);
t_token	*tokens_seperate(char *input);

#endif
