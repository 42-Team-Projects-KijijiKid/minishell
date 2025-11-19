#include "../../../inc/minishell.h"

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

static bool	quote_has_content(char *str)
{
	char	quote;

	quote = *str;
	str++;
	if (quote == *str)
		return (false);
	while (*str != quote && *str)
		str++;
	return (true);
}

static unsigned int	total_length(char *str)
{
	char	*tmp_str;
	int		i;
	int		len_1;
	int		len_2;
	bool	single_quotes;
	bool	double_quotes;

	i = 0;
	len_1 = 0;
	len_2 = 0;
	single_quotes = false;
	double_quotes = false;
	while (*str)
	{
		if (*str == '$' && !single_quotes)
		{
			str++;
			tmp_str = null_end_str(&str);
			tmp_str =  get_environment_value(tmp_str);
			len_1 += ft_strlen(tmp_str);
		}
		else if (!quote_has_content(str))
			str += 2;
		else if (*str == '\'' && !double_quotes)
		{
			single_quotes = !single_quotes;
			str++;
		}
		else if (*str == '\"')
		{
			double_quotes = !double_quotes;
			str++;
		}
		else if (*str && *str != '$')
		{
			len_2++;
			str++;
		}
		else if (*str && *str == '$'
				&& single_quotes)
		{
			len_2++;
			str++;
		}
	}
	return (len_1 + len_2);
}

char	*expand_arguments(char *str)
{
	char				*buffer;
	char				*rtn;
	unsigned int		expanded_len;
	int					i;
	bool				single_quotes;
	bool				double_quotes;
	char				*tmp_str;

	buffer = str;
	expanded_len = total_length(str);
	i = 0;
	rtn = fti_malloc(sizeof(char) * (expanded_len + 1), TEMPORARY);
	single_quotes = false;
	double_quotes = false;
	while (*str)
	{
		if (*str == '$' && !single_quotes)
		{
			str++;
			tmp_str = null_end_str(&str);
			tmp_str =  get_environment_value(tmp_str);
			while (*tmp_str)
			{
				rtn[i] =  *tmp_str;
				i++;
				tmp_str++;
			}
		}
		else if (!quote_has_content(str))
			str += 2;
		else if (*str == '\'' && !double_quotes)
		{
			single_quotes = !single_quotes;
			str++;
		}
		else if (*str == '\"')
		{
			double_quotes = !double_quotes;
			str++; 
		}
		else if (*str && *str != '$')
		{
			rtn[i] = *str;
			i++;
			str++;
		}
		else if (*str && *str == '$'
				&& single_quotes)
		{
			rtn[i] = *str;
			i++;
			str++;
		}
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
		printf("Val: %s\n", *node->args);
		*node->args = expand_arguments(*node->args);
		printf("Val after: %s\n", *node->args);
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
		if (node->args)
			possible_expansion(node);
	}
	expand(node->left);
	expand(node->right);
	return (node);
}



/**
 * 
 * 
 * 	STORING OLD FILES
 * 
 */


//  if (!quote_has_content(*node->args))
// 	*node->args = " ";
// else if (**node->args == '\'')
// 	*node->args = single_quotes(*node->args);
// else if (**node->args == '\"' && quote_has_content(*node->args))
// 	*node->args = double_quotes(*node->args);
// else if (**node->args == '$')
// 	*node->args = argument_expand(*node->args);
// else if (!ft_strncmp(*node->args, "~", ft_strlen(*node->args)))
// 	*node->args = get_environment_value("HOME");



// /// @brief Does not expand the variable
// /// and removes the single quotes leaving the
// /// inner quotes if present
// /// @param str 
// char	*single_quotes(char *str)
// {
// 	int		str_len;
// 	char	*rtn;
// 	int		i;

// 	if (*str == '\'')
// 		str++;
// 	str_len = strlen_whitout_quotes(str, '\'');
// 	rtn = fti_malloc(sizeof(char) * str_len + 1, TEMPORARY);
// 	i = 0;
// 	while (*str != '\'')
// 	{
// 		rtn[i] = *str;
// 		str++;
// 		i++;
// 	}
// 	rtn[i] = '\0';
// 	return (rtn);
// }

// /// @brief Does not expand the variable
// /// and removes the single quotes leaving the
// /// inner quotes if present.
// /// Rebuilds the whole string with expansion.
// /// @param str 
// char	*double_quotes(char *str)
// {
// 	if (*str == '\"')
// 		str++;
// 	else
// 		ft_error("Tried to expand a invalid string", __FILE__, __LINE__, 73);
// 	return (expand_inside_str(str, '\"'));
// }