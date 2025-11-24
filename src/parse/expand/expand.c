#include "../../../inc/minishell.h"

static void	process_non_dollar(char **str, char *rtn, int *i, bool *double_quotes, bool *single_quotes)
{
	if (!quote_has_content(*str) && (!*double_quotes || !*single_quotes))
			*str += 2;
	else if (**str == '\'' && !*double_quotes)
	{
		*single_quotes = !*single_quotes;
		(*str)++;
	}
	else if (**str == '\"' && !*single_quotes)
	{
		*double_quotes = !*double_quotes;
		(*str)++; 
	}
	else if (**str && **str)
	{
		rtn[*i] = **str;
		(*i)++;
		(*str)++;
	}
}

static bool	env_value(char **str, char *rtn, int *i)
{
	char	*tmp_str;

	tmp_str =  give_env_str(str);
	while (tmp_str && *tmp_str)
	{
		rtn[*i] =  *tmp_str;
		(*i)++;
		tmp_str++;
	}
	if (!tmp_str)
		return (false);
	return (true);
}

static bool	check_if_valid(char *str)
{
	str++;
	if (*str == '\0')
		return (false);
	else
		return (true);
	return (false);
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
		if (*str == '$' && !single_quotes
			&& check_if_valid(str))
		{
			// env_value(&str, rtn, &i);
			if (!env_value(&str, rtn, &i)
				&& double_quotes)
				rtn[i++] = '$';
		}
		else
			process_non_dollar(&str, rtn, &i, &double_quotes, &single_quotes);
	}
	rtn[i] = '\0';
	return (rtn);
}

/// @brief Goes trough 2D Array checking
///possible expansions and replacing the strings
void	possible_expansion(t_tree_node *node)
{
	char 			**head;
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