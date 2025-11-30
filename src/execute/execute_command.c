/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:16:43 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:16:45 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/// @brief Checks if command node is a builting
/// and executes if so
/// @param node 
/// @return 0 if its a builtin
/// 1 if builtin is not found
static int	execute_builtin(t_tree_node *node)
{
	int			exit;
	t_minishell	*shell;
	int			len;

	shell = minishell_get();
	exit = -1;
	len = ft_strlen(*node->args);
	if (!ft_strncmp(node->args[0], "cd", len) && len == 2)
		exit = builtin_cd(node->args);
	else if (!ft_strncmp(node->args[0], "echo", len) && len == 4)
		exit = builtin_echo(node->args);
	else if (!ft_strncmp(node->args[0], "exit", len) && len == 4)
		exit = builtin_exit(node->args);
	else if (!ft_strncmp(node->args[0], "export", len) && len == 6)
		exit = builtin_export(node->args);
	else if (!ft_strncmp(node->args[0], "unset", len) && len == 5)
		exit = builtin_unset(node->args);
	else if (!ft_strncmp(node->args[0], "pwd", len) && len == 3)
		exit = builtin_pwd(node->args);
	else if (!ft_strncmp(node->args[0], "env", len) && len == 3)
		exit = builtin_env(node->args);
	if (exit != -1)
		shell->last_exit_status = exit;
	return (exit);
}

static int	execute_redirects(t_tree_node *node)
{
	t_redirect_node	*redirect;
	t_minishell		*shell;
	int				exit_code;

	shell = minishell_get();
	redirect = node->redirect.head;
	exit_code = 0;
	while (redirect && exit_code == 0)
	{
		if (redirect->type == LESS)
			exit_code = execute_rdr_in(redirect);
		else if (redirect->type == GREAT)
			exit_code = execute_rdr_out(redirect);
		else if (redirect->type == DLESS)
			execute_rdr_heredoc(redirect);
		else if (redirect->type == DGREAT)
			exit_code = execute_rdr_append(redirect);
		redirect = redirect->next;
	}
	if (exit_code == 1)
		shell->last_exit_status = exit_code;
	return (exit_code);
}

void	execute_command(t_tree_node *node)
{
	t_minishell	*sh;

	expand(node);
	sh = minishell_get();
	if (node->args == NULL)
		ft_fprintf(2, INVALID_ARGS_EXECUTION, __FILE__);
	if (execute_redirects(node))
		return ;
	if (node->args[0] != NULL)
	{
		if (execute_builtin(node) == -1 && sh->herdoc)
			handle_child_exit(sh, node);
	}
	default_filedescripor();
}
