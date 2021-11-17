/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:11:31 by conobi            #+#    #+#             */
/*   Updated: 2021/11/17 15:52:59 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	f_putchar(char n)
{
	n_write(1, &n, 1);
}

void	f_putstr(char *s)
{
	if (!s)
	{
		f_putstr("(null)");
		return ;
	}
	n_write(1, s, ft_strlen(s));
}

void	f_putnbr(long n, short un)
{
	char	r;

	if (un)
		n = (unsigned)n;
	else
		n = (int)n;
	if (n == 0)
		r = '0';
	else
	{
		if (n < 0)
		{
			n_write(1, "-", 1);
			if (n < (-9))
				f_putnbr(n / 10 * (-1), un);
			r = n % 10 * (-1) + '0';
		}
		else
		{
			if (n > 9)
				f_putnbr(n / 10, un);
			r = n % 10 + '0';
		}
	}
	n_write(1, &r, 1);
}

void	f_putnbr_base(unsigned long long nb, char *base)
{
	char			r;
	unsigned int	base_len;

	base_len = ft_strlen(base);
	if (base_len == 0)
		return ;
	if (nb == 0)
		n_write(1, &base[0], 1);
	else
	{
		if (nb < 0)
		{
			n_write(1, "-", 1);
			if (nb <= base_len * (-1))
				f_putnbr_base(nb / base_len * (-1), base);
			r = base[nb % base_len * (-1)];
		}
		else
		{
			if (nb >= base_len)
				f_putnbr_base(nb / base_len, base);
			r = base[nb % base_len];
		}
		n_write(1, &r, 1);
	}
}

void	f_puthexa(unsigned long long nb, short upper)
{
	if (upper == 2)
		f_putstr("0x");
	if (upper)
		f_putnbr_base(nb, "0123456789abcdef");
	else
		f_putnbr_base(nb, "0123456789ABCDEF");
}
