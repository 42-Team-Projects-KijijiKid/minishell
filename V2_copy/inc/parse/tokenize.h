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
int	    len_in_quotes(char *str);
char	*input_in_quotes(char **str);
bool	quote_content(char **str);
int	    count_arguments(char *str);

#endif
