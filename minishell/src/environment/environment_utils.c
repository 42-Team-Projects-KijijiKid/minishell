#include "../../inc/minishell.h"

char	*env_get_value(char *key)
{
	t_minishell	*shell;
	t_env_node	*node;
	char		*result;
	int			len;

	shell = minishell_get();
	node = shell->env.head;
	while (node)
	{
		if (ft_strncmp(node->key, key, ft_strlen(key)) == 0)
		{
			len = ft_strlen(node->value);
			result = fti_malloc(len + 1, TEMPORARY);
			ft_strlcpy(result, node->value, ft_strlen(result));
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
		if (ft_strncmp(node->key, key, ft_strlen(node->key)) == 0)
		{
			node->value = fti_malloc(ft_strlen(value) + 1, PERSISTENT);
			ft_strlcpy(node->value, value, ft_strlen(value));
			return (0);
		}
		node = node->next;
	}
	new_node = fti_malloc(sizeof(t_env_node), PERSISTENT);
	if (!new_node)
		return (ft_error("Malloc failed", __FILE__, __LINE__, 2), 2);
	new_node->key = fti_malloc(ft_strlen(key) + 1, PERSISTENT);
	ft_strlcpy(new_node->key, key, ft_strlen(key));
	new_node->value = fti_malloc(ft_strlen(value) + 1, PERSISTENT);
	ft_strlcpy(new_node->value, value, ft_strlen(value));
	new_node->next = shell->env.head;
	new_node->prev = NULL;
	if (shell->env.head)
		shell->env.head->prev = new_node;
	shell->env.head = new_node;
	if (!shell->env.tail)
		shell->env.tail = new_node;
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
