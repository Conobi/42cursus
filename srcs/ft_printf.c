/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:10:40 by conobi            #+#    #+#             */
/*   Updated: 2021/11/17 15:50:08 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// int	ft_printf(const char *format, ...)
// {
// 	return (counter(0));
// }

// static void	dumb_joker(char joker)
// {
// 	f_putstr("<JOKER: ");
// 	f_putchar(joker);
// 	f_putstr(">");
// }

static void	f_joker(char jk, va_list args)
{
	if (jk == 'c')
		f_putchar(va_arg(args, int));
	else if (jk == 's')
		f_putstr(va_arg(args, char *));
	else if (jk == 'd' || jk == 'i')
		f_putnbr(va_arg(args, int), 0);
	else if (jk == 'u')
		f_putnbr(va_arg(args, unsigned int), 1);
	else if (jk == 'x')
		f_puthexa(va_arg(args, unsigned int), 1);
	else if (jk == 'X')
		f_puthexa(va_arg(args, unsigned int), 0);
	else if (jk == 'p')
		f_puthexa(va_arg(args, unsigned long long), 2);
	else if (jk == '%')
		f_putchar('%');
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		buf;
	int		ljoker;

	i = -1;
	buf = 0;
	ljoker = 0;
	va_start(args, format);
	while (format[++i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			n_write(1, format + ljoker, buf);
			f_joker(format[i + 1], args);
			i++;
			ljoker = i + 1;
			buf = 0;
		}
		else
			buf++;
	}
	if (buf)
		n_write(1, format + ljoker, buf);
	return (counter(0) + counter(-1));
}
