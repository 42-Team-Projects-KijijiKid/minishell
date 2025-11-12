#include "minishell.h"

/// @brief Goes through environment
/// linked list, and returns value
/// if its in the list
/// @param str To match string without
/// $
/// @return Null or string
char	*rtn_env_value(char *str)
{
	t_minishell	*minishell;
	t_env_node	*env;

	minishell = minishell_get();
	env = minishell->env.head;
	while (env && ft_strncmp(str, env->key, env->key_len) != 0)
		env =env->next;
	if (env)
		return (env->value);
	return (NULL);
}
