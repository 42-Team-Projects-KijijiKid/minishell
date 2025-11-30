/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:16:41 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:16:42 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_array(char **envp)
{
	char	**path_2d;

	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, ft_strlen("PATH=")) == 0)
		{
			path_2d = fti_split((*envp + 5), ':');
			return (path_2d);
		}
		envp++;
	}
	return (NULL);
}

char	*get_bin_path_of_command(char *cmd, char **paths_2d)
{
	char	*path_cmd;
	char	*full_path;

	path_cmd = fti_strjoin("/", cmd, TEMPORARY);
	while (*paths_2d)
	{
		full_path = fti_strjoin(*paths_2d, path_cmd, TEMPORARY);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		paths_2d++;
	}
	return (NULL);
}
