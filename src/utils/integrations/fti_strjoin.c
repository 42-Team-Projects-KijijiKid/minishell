/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fti_strjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:14:08 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:14:20 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fti_strjoin(char const *s1, char const *s2, t_garbage_layers layer)
{
	size_t		i;
	char		*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)fti_malloc(sizeof(char) * (
				ft_strlen(s1) + ft_strlen(s2) + 1), layer);
	if (!str)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		if (i < ft_strlen(s1))
			str[i] = s1[i];
		else
			str[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	str[i] = '\0';
	return (str);
}
