/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:36:32 by mandre            #+#    #+#             */
/*   Updated: 2025/11/20 17:27:57 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putchar(char c)
{
	if (!(*get_error()))
	{
		if (write(1, &c, 1) < 1)
			set_error(1);
	}
	return (1);
}

int	ft_fputchar(int fd, char c)
{
	if (!(*get_error()))
	{
		if (write(fd, &c, 1) < 1)
			set_error(1);
	}
	return (1);
}
