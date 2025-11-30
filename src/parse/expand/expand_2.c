/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:16:07 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:20:32 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_non_dollar(char **str,
	char *rtn, int *i, bool (*quotes)[2])
{
	if (!quote_has_content(*str) && (!(*quotes)[0] || !(*quotes)[1]))
		*str += 2;
	else if (**str == '\'' && !(*quotes)[0])
	{
		(*quotes)[1] = !(*quotes)[1];
		(*str)++;
	}
	else if (**str == '\"' && !(*quotes)[1])
	{
		(*quotes)[0] = !(*quotes)[0];
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
	bool				quotes[2];

	buffer = str;
	expanded_len = total_length(str);
	i = 0;
	rtn = fti_malloc(sizeof(char) * (expanded_len + 1), TEMPORARY);
	quotes[0] = false;
	quotes[1] = false;
	while (*str)
	{
		if (*str == '$' && !quotes[1]
			&& check_char(str))
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
