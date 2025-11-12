#ifndef EXPAND_H
# define EXPAND_H

#include "structs.h"

// expand.c
t_tree_node	*expand_process(t_tree_node *node);

// expand_helpers.c
unsigned int	strlen_with_expansion(char *str, char quote);
char			*expand_inside_str(char *str, char quote);
int				strlen_whitout_quotes(char *str, char quote);

// get_environment_value.c
char	*get_environment_value(char *str);
#endif
