#include "../../../inc/minishell.h"

int get_env_val(char *key)
{
	t_meta *meta = get_meta();
	t_env_node *node = meta->env.head;

	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (ft_strdup(node->value));
		node = node->next;
	}
	return (NULL);
}

int set_env_val(char *key, char *value)
{
	t_meta *meta = get_meta();
	t_env_node *node = meta->env.head;

	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			node->value = ft_strdup(value);
			return (0);
		}
		node = node->next;
	}
	t_env_node *new_node = malloc(sizeof(t_env_node));
	if (!new_node)
		return (ft_error("Malloc failed", __FILE__, __LINE__, 2), 2);
	new_node->key = ft_strdup(key); // New version required, that adds to garbage collector
	new_node->value = ft_strdup(value);
	new_node->next = meta->env.head;
	meta->env.head = new_node;
	return (0);
}

int unset_env_var(char *key)
{
	t_meta *meta = get_meta();
	t_env_node *node = meta->env.head;
	t_env_node *prev = NULL;

	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			if (prev)
				prev->next = node->next;
			else
				meta->env.head = node->next;
			// Free the node, if garbage collector does not handle it anyways
			return (0);
		}
		prev = node;
		node = node->next;
	}
	return (0);
}
