/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:16:53 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:16:54 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	execute_rdr_in(t_redirect_node *redirect)
{
	int	fd;

	fd = open(redirect->file, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_fprintf(2, INFILE_NOT_FOUND, redirect->file);
		return (1);
	}
	else if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		ft_error(DUP2_FAILED, __FILE__, __LINE__, 131);
	}
	close(fd);
	return (0);
}
