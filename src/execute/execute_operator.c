/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:16:38 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:16:39 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_and(t_tree_node *node)
{
	t_minishell	*shell;

	shell = minishell_get();
	execute_node(node->left);
	if (shell->last_exit_status == 0)
		execute_node(node->right);
}

void	execute_or(t_tree_node *node)
{
	t_minishell	*shell;

	shell = minishell_get();
	execute_node(node->left);
	expand(node);
	if (shell->last_exit_status != 0)
		execute_node(node->right);
}
