/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_subshells.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:15:12 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:15:13 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

t_token	*get_last_token(t_token *node)
{
	while (node->next)
		node = node->next;
	return (node);
}

int	count_parenthesis_at_end(t_token *token)
{
	t_token	*last;
	int		count;

	last = get_last_token(token);
	count = 0;
	while (last && last->type == RPAREN)
	{
		count++;
		last = last->prev;
	}
	return (count);
}

int	count_parenthesis_at_start(t_token *token)
{
	int		count;

	count = 0;
	while (token && token->type == LPAREN)
	{
		count++;
		token = token->next;
	}
	return (count);
}

t_token	*get_final_before_parenthesis(t_token *token, bool reverse)
{
	if (reverse)
	{
		while (token->type == LPAREN)
			token = token->next;
	}
	else
	{
		token = get_last_token(token);
		while (token->type == RPAREN)
			token = token->prev;
	}
	return (token);
}
