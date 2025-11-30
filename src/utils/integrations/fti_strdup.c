/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fti_strdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:14:23 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:14:24 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fti_strdup(const char *s, t_garbage_layers layer)
{
	size_t	i;
	size_t	s_len;
	char	*ptr;

	if (s[1] == '/')
		return (fti_strdup("/", TEMPORARY));
	s_len = ft_strlen(s);
	ptr = fti_malloc(sizeof(char) * s_len + 1, layer);
	if (!(ptr))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
