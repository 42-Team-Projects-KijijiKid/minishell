/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:40:44 by mandre            #+#    #+#             */
/*   Updated: 2025/03/27 16:25:30 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*array;
	size_t	i;

	if (!s || !f)
		return (NULL);
	array = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!array)
		return (NULL);
	array[ft_strlen(s)] = '\0';
	i = 0;
	while (i < ft_strlen(s))
	{
		array[i] = (*f)(i, s[i]);
		i++;
	}
	array[i] = '\0';
	return (array);
}
