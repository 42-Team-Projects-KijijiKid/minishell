/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:16:46 by mandre            #+#    #+#             */
/*   Updated: 2025/11/20 17:56:42 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	fprint_conversions(int fd, const char *specifier, va_list *ap)
{
	if (*specifier == 'c')
		return (ft_fputchar(fd, va_arg(*ap, int)));
	if (*specifier == 's')
		return (fprint_str(fd, va_arg(*ap, char *)));
	if (*specifier == 'p')
		return (fprint_ptr(fd, (unsigned long)va_arg(*ap, void *)));
	if (*specifier == 'i' || *specifier == 'd')
		return (fprint_int(fd, va_arg(*ap, int), 0));
	if (*specifier == 'u')
		return (fprint_usigned(fd, va_arg(*ap, unsigned int), 0));
	if (*specifier == 'x')
		return (fhexa_lowercase(fd, va_arg(*ap, unsigned int), 0));
	if (*specifier == 'X')
		return (fhexa_uppercase(fd, va_arg(*ap, unsigned int), 0));
	if (*specifier == '%')
		return (ft_fputchar(fd, '%'));
	return (0);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	int		total;
	va_list	ap;

	total = 0;
	va_start(ap, str);
	set_error(0);
	while (*str)
	{
		if (*str == '%')
			total += fprint_conversions(fd, ++str, &ap);
		else
			total += ft_fputchar(fd, *str);
		if (*(get_error()) == 1)
		{
			va_end(ap);
			return (-1);
		}
		str++;
	}
	va_end(ap);
	return (total);
}
