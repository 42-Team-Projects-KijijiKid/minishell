#ifndef TOKENIZE_H
# define TOKENIZE_H

#include "../structs.h"

// tokenize.c
bool	is_meta_char(char input);
t_token	*tokenize(char *input);

// tokens_find_root.c
t_token	*find_root(t_token *token_head);

// tokens_split_args.c
char	**tokens_split_args(char **input);

// tokens_split_utils.c
unsigned int	count_arguments(char *str);

// tokens_validate.c
bool	is_operator(e_tree_node_type type);
int		count_token_type(t_token *token, e_tree_node_type type);
bool	validate_subshells(t_token *token);
bool	validate_redirects(t_token *token);
bool	validate_operators(t_token *token);
void	tokens_validate(t_token *token);

#endif
