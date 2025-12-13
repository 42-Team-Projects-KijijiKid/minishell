#include "../../../inc/minishell.h"

static char	*get_env_key_from_string(char *string)
{
	int		i;
	char	*key;

	i = 0;
	if (string[i] && (ft_isalpha(string[i]) || string[i] == '_'))
		i++;
	while (string[i] && (ft_isalnum(string[i]) || string[i] == '_'))
		i++;
	key = fti_malloc(i + 1, TEMPORARY);
	key[i--] = '\0';
	while (i >= 0)
	{
		key[i] = string[i];
		i--;
	}
	return (key);
}

/// @brief Goes through environment
/// linked list, and returns value
/// if its in the list
/// @param str Environment key
/// @return NULL or environment
char	*get_environment_value(char *str)
{
	t_minishell		*minishell;
	t_env_node		*env;
	unsigned int	len;
	char			*empty;

	if (!str)
		ft_error("NULL emvironment variable key", __FILE__, __LINE__, 1);
	str = get_env_key_from_string(str);
	len = ft_strlen(str);
	minishell = minishell_get();
	env = minishell->env.head;
	while (env)
	{
		if (env->key_len == len
			&& ft_strncmp(str, env->key, len) == 0)
			break ;
		env = env->next;
	}
	if (env)
		return (env->value);
	empty = fti_malloc(1, TEMPORARY);
	*empty = '\0';
	return (empty);
}
