#include "../../inc/minishell.h"

void environment_initialize(char **env_vars)
{
	t_minishell	*shell;
	t_env_node	*node;
	t_env_node	*head;

	shell = minishell_get();
	head = NULL;
	while (*env_vars)
	{
		node = ft_malloc(sizeof(t_env_node), PERSISTENT);
		if (head)
			head->prev = node;
		else
			shell->env.tail = node;
		node->next = head;
		node->key = abstract_key(env_vars);
		node->value = abstract_value(env_vars);
		node->key_len = ft_strlen(node->key);
		node->value_len = ft_strlen(node->value);
		env_vars++;
		head = node;
		shell->env.size++;
	}
	shell->env.head = head;
	head->prev = NULL;
}
