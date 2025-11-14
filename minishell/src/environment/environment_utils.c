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

	len = node->value_len + node->key_len + 1;
	rtn = fti_malloc(sizeof(char) * (len + 1), TEMPORARY);
	i = 0;
	while (node->key[i])
	{
		rtn[i] = node->key[i];
		i++;
	}
	rtn[i++] = '=';
	while (node->value[i])
	{
		rtn[i] = node->value[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

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
			ft_strlcpy(result, node->value,node->value_len + 1);
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
		if (ft_strncmp(node->key, key, ft_strlen(key)) == 0)
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
	ft_strlcpy(new_node->key, key, ft_strlen(key) + 1);
	new_node->value = fti_malloc(ft_strlen(value) + 1, PERSISTENT);
	ft_strlcpy(new_node->value, value, ft_strlen(value) + 1);
	new_node->next = shell->env.head;
	new_node->prev = NULL;
	if (shell->env.head)
		shell->env.head->prev = new_node;
	shell->env.head = new_node;
	if (!shell->env.tail)
		shell->env.tail = new_node;
	shell->env.size++;
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
char	**env_list_to_2d(void) // turn_2d() in expansion/create_inv.c
{
	t_minishell	*shell;
	t_env_node	*node;
	char		**rtn;
	int			i;
	
	shell = minishell_get();
	rtn = fti_malloc(sizeof(char *) * (shell->env.size + 1), PERSISTENT);
	node = shell->env.tail;
	i = 0;
	while (node)
	{
		rtn[i] = rtn_key_value(node);
		node = node->prev;
		i++; 
	}
	rtn[i] = NULL;
	return (rtn);
}