#ifndef EXPAND_H
# define EXPAND_H

#include "structs.h"

// expand_quotes.c
int		calculate_quoted_content_length(char *content, char closing_quote);
char	*extract_single_quoted_content(char *quoted_str);

// expand_variables.c
char	*extract_double_quoted_with_expansion(char *quoted_str);
char	*expand_standalone_variable(char *variable_str);
void	expand(t_tree_node *node);

// expand.c
void	expand_arguments_in_node(t_tree_node *node);
void	expand(t_tree_node *node);

#endif
