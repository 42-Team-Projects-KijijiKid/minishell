#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

// env_initialize.c
unsigned int	env_len_to_equal(char *str);
char			*env_key_from_str(char **str);
char			*env_value_from_str(char **str);
void			environment_initialize(char **envp);

// environment_utils.c
char			*env_get_value(char *key);
int				env_set_value(char *key, char *value);
int				env_unset_value(char *key);
char			*rtn_key_value(t_env_node *node);
char			**env_list_to_2d(void);
void			add_new_env_var(char *key, char *value);

#endif