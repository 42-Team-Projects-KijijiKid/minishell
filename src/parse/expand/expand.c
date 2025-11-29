#include "minishell.h"

static bool	check_single_variable(char **array)
{
	int	i;

	if (!*array)
		return (false);
	if (!array[1])
	{
		i = 0;
		while (is_whitespace(array[0][i]))
		{
			if (!array[0][i])
				return (true);
			i++;
		}
		if (array[0][i] != '$')
			return (false);
		i++;
		while (array[0][i])
		{
			if (array[0][i] == '$')
				return (false);
			if (is_whitespace(array[0][i]))
			{
				while (is_whitespace(array[0][i]))
				{
					if (!array[0][i])
						return (true);
					i++;
				}
				return (false);
			}
			i++;
		}
		return (true);
	}
	return (false);
}

static void	expand_single_variable(t_tree_node *node)
{
	int		i;
	int		len;
	char	*env_key;
	char	*env_value;

	i = 1;
	len = 0;
	while (node->args[0][i] && !is_whitespace(node->args[0][i++]))
		len++;
	i = 1;
	env_key = (char *)fti_malloc(len + 1, TEMPORARY);
	while (node->args[0][i] && !is_whitespace(node->args[0][i]))
	{
		env_key[i - 1] = node->args[0][i];
		i++;
	}
	env_key[i - 1] = '\0';
	env_value = get_environment_value(env_key);
	node->args = fti_split(env_value, ' ');
}

/// @brief Goes recursively through the
/// bimary tree and searches for 
/// posisble expansions
/// @param node 
/// @return recursive calls of
/// nodes to avoid destruction
/// of binary tree
t_tree_node	*expand(t_tree_node *node)
{
	if (!node)
		return (NULL);
	if (node->type == TEXT)
	{
		if (node->args)
		{
			if (check_single_variable(node->args))
				expand_single_variable(node);
			else
				expand_arguments(node);
		}
	}
	expand(node->left);
	expand(node->right);
	return (node);
}
