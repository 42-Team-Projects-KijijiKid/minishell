/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:48:20 by mandre            #+#    #+#             */
/*   Updated: 2025/03/27 10:22:07 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		((unsigned char *)tmp)[i] = 0;
		i++;
	}
	return (tmp);
}
