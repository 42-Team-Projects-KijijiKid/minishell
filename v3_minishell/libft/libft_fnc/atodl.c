/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atodl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateoandre <mateoandre@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:11:38 by mateoandre        #+#    #+#             */
/*   Updated: 2025/09/13 11:23:38 by mateoandre       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_ws_and_get_sign(const char **s)
{
	int	sign;

	sign = 1;
	while (**s == 32 || (9 <= **s && **s <= 13))
		(*s)++;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	return (sign);
}

/// @brief This takes an String double number
/// written as string and converts it to double
/// @param s string to convert
/// @return converted double number
double	atodl(char *s)
{
	long		integer_part;
	double		fractional_part;
	double		pow;
	int			sign;
	const char	*p = s;

	integer_part = 0;
	fractional_part = 0;
	pow = 1;
	sign = skip_ws_and_get_sign(&p);
	while (*p != '.' && *p)
		integer_part = (10 * integer_part) + (*p++ - '0');
	if (*p == '.')
		p++;
	while (*p)
	{
		pow /= 10;
		fractional_part = fractional_part + (*p++ - '0') * pow;
	}
	return ((integer_part + fractional_part) * sign);
}
