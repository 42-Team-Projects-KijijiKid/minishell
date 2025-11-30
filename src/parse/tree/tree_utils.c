/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:15:09 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:15:10 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/// @brief Nulls every value of the token.
/// Safety wise.
/// @param token 
static void	initialize_tree_node(t_tree_node *node)
{
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->sub = false;
	node->redirect.head = NULL;
	node->redirect.tail = NULL;
	node->redirect.size = 0;
}

t_tree_node	*token_to_tree_node(t_token *head_token)
{
	t_tree_node	*node;

	node = (t_tree_node *)fti_malloc(sizeof(t_tree_node), TEMPORARY);
	initialize_tree_node(node);
	node->args = head_token->args;
	node->type = head_token->type;
	node->redirect.head = NULL;
	return (node);
}
