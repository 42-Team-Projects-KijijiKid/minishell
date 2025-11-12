#include "minishell.h"

/// @brief Goes through environment
/// linked list, and returns value
/// if its in the list
/// @param str Environment key
/// @return NULL or environment
char	*get_environment_value(char *str)
{
	t_minishell	*minishell;
	t_env_node	*env;
	int			len;

	len = ft_strlen(str);
	minishell = minishell_get();
	env = minishell->env.head;
	while (env)
	{
		if (env->key_len == len
			&& ft_strncmp(str, env->key, len) == 0)
			break ;
		env =env->next;
	}
	if (env)
		return (env->value);
	return (NULL);
}
