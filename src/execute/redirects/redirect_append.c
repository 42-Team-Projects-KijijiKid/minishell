/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:16:58 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:16:59 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	execute_rdr_append(t_redirect_node *redirect)
{
	int	fd;

	fd = open(redirect->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_fprintf(2, INFILE_NOT_FOUND, redirect->file);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		ft_error(DUP2_FAILED, __FILE__, __LINE__, 131);
	}
	close(fd);
	return (0);
}
