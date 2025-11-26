#include "../../inc/minishell.h"

/// @brief This is kinda like stringjoin
/// just takes the key and the value and
/// glues them togther, seperated by an
/// equal sign
/// @param node key and value node
/// @return 
char	*rtn_key_value(t_env_node *node)
{
	int		len;
	char	*rtn;
	int		i;
	int		x;

	if (!node)
		return (NULL);
	len = node->value_len + node->key_len + 1;
	rtn = fti_malloc(sizeof(char) * (len + 1), TEMPORARY);
	i = 0;
	while (node->key[i])
	{
		rtn[i] = node->key[i];
		i++;
	}
	if (!node->value)
	{
		rtn[i] = '\0';
		return (rtn);
	}
	rtn[i++] = '=';
	x = 0;
	while (node->value[x])
	{
		rtn[i] = node->value[x];
		i++;
		x++;
	}
	rtn[i] = '\0';
	return (rtn);
}

char	*env_get_value(char *key)
{
	t_minishell	*shell;
	t_env_node	*node;
	char		*result;

	shell = minishell_get();
	node = shell->env.head;
	while (node)
	{
		if (ft_strncmp(node->key, key, ft_strlen(key)) == 0)
		{
			result = fti_malloc(node->value_len + 1, TEMPORARY);
			ft_strlcpy(result, node->value, node->value_len + 1);
			return (result);
		}
		node = node->next;
	}
	return (NULL);
}

int	env_set_value(char *key, char *value)
{
	t_minishell	*shell;
	t_env_node	*node;
	t_env_node	*new_node;

	shell = minishell_get();
	node = shell->env.head;
	while (node)
	{
		if (ft_strncmp(node->key, key, ft_strlen(key)) == 0
			&& node->key_len == ft_strlen(key))
		{
			node->value = fti_strdup(value, PERSISTENT);
			node->value_len = ft_strlen(node->value);
			return (0);
		}
		node = node->next;
	}
	add_new_env_var(key, value);
	return (0);
}

int	env_unset_value(char *key)
{
	t_minishell	*shell;
	t_env_node	*node;

	shell = minishell_get();
	node = shell->env.head;
	while (node)
	{
		if (ft_strncmp(node->key, key, ft_strlen(key)) == 0)
		{
			if (node->prev)
				node->prev->next = node->next;
			else
				shell->env.head = node->next;
			if (node->next)
				node->next->prev = node->prev;
			else
				shell->env.tail = node->prev;
			return (0);
		}
		node = node->next;
	}
	return (0);
}

/// @brief This function turns the
/// env linked list in 2D array for
/// execeve
/// @param  
/// @return 2D array of env variables 
char	**env_list_to_2d(void)
{
	t_minishell	*shell;
	t_env_node	*node;
	char		**rtn;
	int			i;

	shell = minishell_get();
	rtn = fti_malloc(sizeof(char *) * (shell->env.size + 1), TEMPORARY);
	node = shell->env.head;
	if (!node)
		return (NULL);
	i = 0;
	while (node)
	{
		rtn[i] = rtn_key_value(node);
		node = node->next;
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}
