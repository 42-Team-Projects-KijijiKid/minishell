#include "../../inc/minishell.h"

/// @brief return the len to the
/// equal sign 
/// @param str 
/// @return length of cahrs till equal sign
unsigned int	env_len_to_equal(char *str)
{
	unsigned int	i;

	i = 0;
	while (*str != '=')
	{
		str++;
		i++;
	}
	return (i);
}

/// @brief Abstracts the key of env var
/// Skips away the equal sign so
/// env_value_from_str can begin copy directly
/// @param str 
/// @return NULL terminated key
/// without the equal sign
char	*env_key_from_str(char **str)
{
	char	*rtn;
	int		len;
	int		i;

	len = env_len_to_equal(*str);
	rtn = fti_malloc(sizeof(char) * (len + 1), PERSISTENT);
	i = 0;
	while (**str != '=')
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	if (**str == '=')
		(*str)++;
	rtn[i] = '\0';
	return (rtn);
}

/// @brief Asbtarcts the value of env var
/// @param str 
/// @return NULL terminated value 
/// without the equal sign
char	*env_value_from_str(char **str)
{
	char	*rtn;
	int		len;
	int		i;

	len = ft_strlen(*str);
	rtn = fti_malloc(sizeof(char) * (len + 1), PERSISTENT);
	i = 0;
	while (**str)
	{
		rtn[i] = **str;
		(*str)++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

void environment_initialize(char **env_vars)
{
	t_minishell	*shell;
	t_env_node	*node;
	t_env_node	*new_node;

	shell = minishell_get();
	node = fti_malloc(sizeof(t_env_node), PERSISTENT);
	node->prev = NULL;
	shell->env.head = node;
	while (*env_vars && env_vars)
	{
		shell->env.size++;
		node->key = env_key_from_str(env_vars);
		node->value = env_value_from_str(env_vars);
		node->key_len = ft_strlen(node->key);
		node->value_len = ft_strlen(node->value);
		env_vars++;
		if (env_vars && *env_vars)
			new_node = fti_malloc(sizeof(t_env_node), PERSISTENT);
		else
			break ;
		node->next = new_node;
		node = new_node;
	}
	node->next = NULL;
	shell->env.tail = node;
}
