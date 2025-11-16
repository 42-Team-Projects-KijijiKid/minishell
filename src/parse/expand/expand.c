#include "../../../inc/minishell.h"

/// @brief Does not expand the variable
/// and removes the single quotes leaving the
/// inner quotes if present
/// @param str 
char	*single_quotes(char *str)
{
	int		str_len;
	char	*rtn;
	int		i;

	if (*str == '\'')
		str++;
	str_len = strlen_whitout_quotes(str, '\'');
	rtn = fti_malloc(sizeof(char) * str_len + 1, TEMPORARY);
	i = 0;
	while (*str != '\'')
	{
		rtn[i] = *str;
		str++;
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

/// @brief Does not expand the variable
/// and removes the single quotes leaving the
/// inner quotes if present.
/// Rebuilds the whole string with expansion.
/// @param str 
char	*double_quotes(char *str)
{
	if (*str == '\"')
		str++;
	else
		ft_error("Tried to expand a invalid string", __FILE__, __LINE__, 73);
	return (expand_inside_str(str, '\"'));
}

char	*argument_expand(char *str)
{
	char	*rtn;
	char	*tmp_str;
	int		i;
	int		len;

	len = strlen_with_expansion(str, '\'');
	rtn = fti_malloc((sizeof(char) * len) + 1, TEMPORARY);
	i = 0;
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			tmp_str = null_end_str(&str);
			tmp_str =  get_environment_value(tmp_str);
			while (tmp_str && *tmp_str)
			{
				rtn[i++] = *tmp_str;
				tmp_str++;
			}
		}
		if (*str && *str != '$')
			str++;
	}
	rtn[i] = '\0';
	return (rtn);
}

/// @brief Goes trough 2D Array checking
///possible expansions and replacing the strings
void	possible_expansion(t_tree_node *node)
{
	char **head;

	head = node->args;
	while (*node->args)
	{
		if (**node->args == '\'')
			*node->args = single_quotes(*node->args);
		else if (**node->args == '\"')
			*node->args = double_quotes(*node->args);
		else if (**node->args == '$')
			*node->args = argument_expand(*node->args);
		node->args++;
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
		if (*node->args && node->args[1])
			possible_expansion(node);
	}
	expand(node->left);
	expand(node->right);
	return (node);
}
