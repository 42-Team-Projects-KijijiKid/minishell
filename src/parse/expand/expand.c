#include "../../../inc/minishell.h"

char	*expand_arguments(char *str)
{
	char				*rtn;
	unsigned int		expanded_len;
	int					i;
	bool				quotes[2];

	expanded_len = total_length(str);
	if (expanded_len == 0)
		return (NULL);
	i = 0;
	rtn = fti_malloc(sizeof(char) * (expanded_len + 1), TEMPORARY);
	quotes[0] = false;
	quotes[1] = false;
	while (*str)
	{
		if (*str == '$' && !quotes[1]
			&& check_if_valid(str))
		{
			if (!env_value(&str, rtn, &i) && quotes[0])
				rtn[i++] = '$';
		}
		else
			process_non_dollar(&str, rtn, &i, &quotes);
	}
	return (rtn[i] = '\0', rtn);
}

/// @brief Goes trough 2D Array checking
///possible expansions and replacing the strings
void	possible_expansion(t_tree_node *node)
{
	char			**head;
	t_redirect_node	*redir;

	head = node->args;
	while (*node->args)
	{
		if (ft_strncmp(*node->args, "~", ft_strlen(*node->args)) == 0)
			*node->args = get_environment_value("HOME");
		else
			*node->args = expand_arguments(*node->args);
		node->args++;
	}
	redir = node->redirect.head;
	while (redir)
	{
		if (ft_strncmp(redir->file, "~", ft_strlen(redir->file)) == 0)
			redir->file = get_environment_value("HOME");
		else
			redir->file = expand_arguments(redir->file);
		redir = redir->next;
	}
	node->args = head;
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
			possible_expansion(node);
	}
	expand(node->left);
	expand(node->right);
	return (node);
}
