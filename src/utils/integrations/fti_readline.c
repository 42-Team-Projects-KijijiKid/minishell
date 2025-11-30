/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fti_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:14:32 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:14:33 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*fti_readline(char *promt)
{
	char		*cmd;
	int			len;

	cmd = NULL;
	while (1)
	{
		cmd = readline(promt);
		if (!cmd)
		{
			ft_fprintf(1, "\n");
			return (NULL);
		}
		len = ft_strlen(cmd);
		if (len != 0)
		{
			add_history(cmd);
			return (cmd);
		}
		else
			continue ;
	}
}
