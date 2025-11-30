/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:17:04 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:17:05 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	builtin_pwd(char **args)
{
	char	*pwd;

	(void)args;
	pwd = env_get_value("PWD");
	if (!pwd)
		ft_error("pwd: PWD not set", __FILE__, __LINE__, 930);
	ft_fprintf(1, "%s\n", pwd);
	return (0);
}
