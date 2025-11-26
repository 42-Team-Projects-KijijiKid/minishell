#ifndef EXPAND_H
# define EXPAND_H

# include "../structs.h"

// expand.c
t_tree_node		*expand(t_tree_node *node);

// expand_helpers.c
unsigned int	strlen_with_expansion(char *str, char quote);
char			*expand_inside_str(char *str, char quote);
char			*null_end_str(char **str);
bool			quote_has_content(char *str);
char			*give_env_str(char **str);

// expand_total_len.c
unsigned int	total_length(char *str);

// get_environment_value.c
char			*get_environment_value(char *str);
#endif
