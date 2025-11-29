#include "minishell.h"

static void	process_non_dollar(char **str,
	char *rtn, int *i, bool *double_quotes, bool *single_quotes)
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
	else if (**str && **str != '\\')
	{
		rtn[*i] = **str;
		(*i)++;
		(*str)++;
	}
	else
	{
		if (**str == '\\')
			(*str)++;
		rtn[(*i)++] = **str;
		(*str)++;
	}
}

char	*expand_single_argument(char *str)
{
	char				*buffer;
	char				*rtn;
	unsigned int		expanded_len;
	int					i;
	bool				single_quotes;
	bool				double_quotes;

	buffer = str;
	expanded_len = total_length(str);
	i = 0;
	rtn = fti_malloc(sizeof(char) * (expanded_len + 1), TEMPORARY);
	single_quotes = false;
	double_quotes = false;
	while (*str)
	{
		if (*str == '$' && !single_quotes
			&& check_char(str))
		{
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
void	expand_arguments(t_tree_node *node)
{
	char			**head;
	t_redirect_node	*redir;

	head = node->args;
	while (*node->args)
	{
		if (ft_strncmp(*node->args, "~", ft_strlen(*node->args)) == 0)
			*node->args = get_environment_value("HOME");
		else
			*node->args = expand_single_argument(*node->args);
		node->args++;
	}
	redir = node->redirect.head;
	while (redir)
	{
		if (ft_strncmp(redir->file, "~", ft_strlen(redir->file)) == 0)
			redir->file = get_environment_value("HOME");
		else
			redir->file = expand_single_argument(redir->file);
		redir = redir->next;
	}
	node->args = head;
}
