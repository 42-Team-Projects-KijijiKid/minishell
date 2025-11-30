/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:13:26 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:13:28 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_shell_level(void)
{
	char	*lvl_str;
	int		lvl_int;

	lvl_str = env_get_value("SHLVL");
	lvl_int = ft_atoi(lvl_str);
	lvl_int++;
	lvl_str = fti_itoa(lvl_int);
	env_set_value("SHLVL", lvl_str);
}
