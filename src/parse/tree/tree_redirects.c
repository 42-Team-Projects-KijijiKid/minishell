/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:15:17 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:15:19 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	is_redirect(t_tree_node_type type)
{
	if (type == DGREAT)
		return (true);
	else if (type == DLESS)
		return (true);
	else if (type == GREAT)
		return (true);
	else if (type == LESS)
		return (true);
	return (false);
}

void	build_redirect(t_build_manager *manager,
	t_redirect_node **redirect, t_token **token)
{
	if (manager->root_node->redirect.head == NULL)
		manager->root_node->redirect.head = *redirect;
	(*redirect)->type = (*token)->type;
	(*redirect)->file = (*token)->next->args[0];
	(*redirect)->next = NULL;
	*token = (*token)->next;
	*token = (*token)->next;
	if ((*token) && is_redirect((*token)->type))
		(*redirect)->next = (t_redirect_node *)fti_malloc(
				sizeof(t_redirect_node), TEMPORARY);
	*redirect = (*redirect)->next;
}

void	tree_redirects(t_build_manager *manager)
{
	t_token			*token;
	t_redirect_node	*redirect;

	if (!manager->head_token->next)
		return ;
	token = manager->head_token;
	if (manager->head_token->type == TEXT
		&& manager->head_token == manager->root_token)
		token = manager->head_token->next;
	else if (is_redirect(manager->head_token->type))
	{
		token = manager->head_token;
		manager->root_node->args = (char **)fti_malloc(
				sizeof(char *), TEMPORARY);
		manager->root_node->args[0] = NULL;
	}
	redirect = NULL;
	if (token && is_redirect(token->type))
		redirect = (t_redirect_node *)fti_malloc(sizeof(
					t_redirect_node), TEMPORARY);
	while (token && is_redirect(token->type))
		build_redirect(manager, &redirect, &token);
}
