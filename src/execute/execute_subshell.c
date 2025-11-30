/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:16:30 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:16:32 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_subshell(t_tree_node *node)
{
	int			pid;
	t_minishell	*shell;
	int			status;

	pid = ft_fork();
	shell = minishell_get();
	if (pid == -1)
		ft_error("Fork failed", __FILE__, __LINE__, 92);
	if (pid == 0)
	{
		execute_node_by_type(node);
		garbage_free_all();
		exit(shell->last_exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status))
			ft_error("Unexpected error in subshell execution",
				__FILE__, __LINE__, 991);
	}
}
