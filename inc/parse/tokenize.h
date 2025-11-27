#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "../structs.h"

// tokenize.c
t_token				*tokenize(char *input);

//tokenize_helpers.c
t_tree_node_type	evaluate_token_type(char **input);
bool				is_meta_char(char input);

// tokens_find_root.c
t_token				*find_root(t_token *token_head);

// tokens_split_args.c
char				**tokens_split_args(char **input);

// tokens_split_utils.c
unsigned int		count_arguments(char *str);

// tokens_validate.c
bool				validate_subshells(t_token *token);
bool				validate_redirects(t_token *token);
bool				validate_operators(t_token *token);
int					tokens_validate(t_token *token);

// tokens_validate_2.c
bool				is_operator(t_tree_node_type type);
int					count_token_type(t_token *token, t_tree_node_type type);

#endif