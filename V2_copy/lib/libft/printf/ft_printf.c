/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateoandre <mateoandre@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:52:44 by mateoandre        #+#    #+#             */
/*   Updated: 2025/09/08 11:49:35 by mateoandre       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	print_conversions(const char *specifier, va_list *ap)
{
	if (*specifier == 'c')
		return (ft_putchar(va_arg(*ap, int)));
	if (*specifier == 's')
		return (print_str(va_arg(*ap, char *)));
	if (*specifier == 'p')
		return (print_ptr((unsigned long)va_arg(*ap, void *)));
	if (*specifier == 'i' || *specifier == 'd')
		return (print_int(va_arg(*ap, int), 0));
	if (*specifier == 'u')
		return (print_usigned(va_arg(*ap, unsigned int), 0));
	if (*specifier == 'x')
		return (hexa_lowercase(va_arg(*ap, unsigned int), 0));
	if (*specifier == 'X')
		return (hexa_uppercase(va_arg(*ap, unsigned int), 0));
	if (*specifier == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		total;
	va_list	ap;

	total = 0;
	va_start(ap, str);
	set_error(0);
	while (*str)
	{
		if (*str == '%')
			total += print_conversions(++str, &ap);
		else
			total += ft_putchar(*str);
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

// int main(void)
// {
//     char singleChar = '%';
//     char *stringText = "";
//     void *voidPointer = &singleChar;
//     int number = 6329;
//     unsigned int unsignedNum = -1;
//     int hexNum = 23889;

//     printf("\n---------Char-----------\n");
// 	printf("My-Return: %d\n", ft_printf("My: %c\n", singleChar));
// 	printf("Printf-Return: %d\n", printf("Printf: %c\n", singleChar) - 4);
//     printf("\n---------String-----------\n");
// 	printf("My-Return: %d\n", ft_printf("My: %s\n", stringText));
// 	printf("Printf-Return: %d\n", printf("Printf: %s\n", stringText) - 4);
//     printf("\n---------Void-Pointer-----------\n");
// 	printf("My-Return: %d\n", ft_printf("My: %p\n", voidPointer));
// 	printf("Printf-Return: %d\n", printf("Printf: %p\n", voidPointer) - 4);
//     printf("\n---------Decimal-----------\n");
// 	printf("My-Return: %d\n", ft_printf("My: %d\n", number));
// 	printf("Printf-Return: %d\n", printf("Printf: %d\n", number) - 4);
//     printf("\n---------Integer-----------\n");
// 	printf("My-Return: %d\n", ft_printf("My: %i\n", number));
// 	printf("Printf-Return: %d\n", printf("Printf: %i\n", number) - 4);
//     printf("\n---------Unsigned Decimal-----------\n");
// 	printf("My-Return: %d\n", ft_printf("My: %u\n", unsignedNum));
// 	printf("Printf-Return: %d\n", printf("Printf: %u\n", unsignedNum) - 4);
//     printf("\n---------Hexa-lowercase-----------\n");
// 	printf("My-Return: %d\n", ft_printf("My: %x\n", hexNum));
// 	printf("Printf-Return: %d\n", printf("Printf: %x\n", hexNum) - 4);
//     printf("\n---------Hexa-Uppercase-----------\n");
// 	printf("My-Return: %d\n", ft_printf("My: %X\n", hexNum));
// 	printf("Printf-Return: %d\n", printf("Printf: %X\n", hexNum) - 4);
//     printf("\n---------Just%%-----------\n");
// 	printf("My-Return: %d\n", ft_printf("My: %%\n"));
// 	printf("Printf-Return: %d\n", printf("Printf: %%\n") - 4);
// }