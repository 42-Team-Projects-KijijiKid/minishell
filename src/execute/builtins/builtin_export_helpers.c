#include "minishell.h"

void	export_to_env(char *str)
{
	t_minishell	*shell;
	t_env_node	*node;
	char		*key;
	char		*value;

	shell = minishell_get();
	key = extract_key(str);
	value = extract_value(str);
	node =  shell->env.head;
	while (node)
	{
		if (ft_strncmp(node->key, key, ft_strlen(key)) == 0
			&& node->key_len == ft_strlen(key))
		{
			node->value = fti_strdup(value, PERSISTENT);
			node->value_len = ft_strlen(node->value);
			return ;
		}
		node = node->next;
	}
	add_new_env_var(key, value);
}

void	concatenate_env(char *str)
{
	t_minishell	*shell;
	t_env_node	*node;
	char		*key;
	char		*value;

	shell = minishell_get();
	key = extract_key(str);
	value = extract_value(str);
	node =  shell->env.head;
	while (node)
	{
		if (ft_strncmp(node->key, key, ft_strlen(key)) == 0
			&& node->key_len == ft_strlen(key))
		{
			node->value = fti_strjoin(node->value, value, PERSISTENT);
			node->value_len = ft_strlen(node->value);
			return ;
		}
		node = node->next;
	}
	add_new_env_var(key, value);
}

bool	has_value(char *str)
{
	while (*str && *str != '=')
		str++;
	if (*str && *str == '=')
		str++;
	if (!*str)
		return (false);
	return (true);
}

bool	has_valid_key(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
	{
		ft_fprintf(STDERR_FILENO, INVALID_IDENTIFIER, str);
		return (false);
	}
	else
		str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_'
			&& *str != '+')
			return (false);
		str++;
	}
	return (true);
}
