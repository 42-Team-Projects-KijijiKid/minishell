/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_validate_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:15:35 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:15:36 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(t_tree_node_type type)
{
	if (type == AND_IF)
		return (true);
	else if (type == OR_IF)
		return (true);
	else if (type == PIPE)
		return (true);
	return (false);
}

int	count_token_type(t_token *token, t_tree_node_type type)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == type)
			count++;
		token = token->next;
	}
	return (count);
}
