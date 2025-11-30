/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:15:01 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:15:03 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	*get_error_code(void)
{
	static int	error_code = 0;

	return (&error_code);
}

int	minishell_parse(char *input)
{
	t_minishell		*shell;
	t_build_manager	manager;

	shell = minishell_get();
	validate_quote_pairs(input);
	if (*get_error_code())
		return (*get_error_code());
	manager.head_token = tokenize(input);
	if (*get_error_code())
		return (*get_error_code());
	tokens_validate(manager.head_token);
	if (*get_error_code())
		return (*get_error_code());
	manager.root_token = find_root(manager.head_token);
	if (*get_error_code())
		return (*get_error_code());
	manager.root_node = token_to_tree_node(manager.root_token);
	shell->tree_root = manager.root_node;
	tree_build(&manager);
	return (shell->last_exit_status);
}
