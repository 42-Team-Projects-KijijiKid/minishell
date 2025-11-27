#ifndef EXPAND_H
# define EXPAND_H

# include "../structs.h"

// expand.c
t_tree_node		*expand(t_tree_node *node);

// expand_2.c
void			process_non_dollar(char **str, char *rtn,
					int *i, bool (*quotes)[2]);
bool			env_value(char **str, char *rtn, int *i);
bool			check_if_valid(char *str);

// expand_helpers.c
unsigned int	strlen_with_expansion(char *str, char quote);
char			*expand_inside_str(char *str, char quote);
char			*give_env_str(char **str);

// expand_helpers_2.c
char			*null_end_str(char **str);
bool			quote_has_content(char *str);

// expand_total_len.c
unsigned int	total_length(char *str);

// get_environment_value.c
char			*get_environment_value(char *str);

#endif