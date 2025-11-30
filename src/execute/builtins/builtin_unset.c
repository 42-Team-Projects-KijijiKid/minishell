/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:17:01 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:17:02 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	builtin_unset(char **args)
{
	int	i;

	if (!args || !(*args))
		ft_error("Builtin not set", __FILE__, __LINE__, 21);
	i = 1;
	while (args[i])
	{
		env_unset_value(args[i]);
		i++;
	}
	return (0);
}
