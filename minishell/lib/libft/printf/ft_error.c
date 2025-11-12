/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateoandre <mateoandre@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:38:36 by mandre            #+#    #+#             */
/*   Updated: 2025/09/08 11:49:28 by mateoandre       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	*get_error(void)
{
	static int	status = 0;

	return (&status);
}

void	set_error(int new_status)
{
	int	*status;

	status = get_error();
	*status = new_status;
}
