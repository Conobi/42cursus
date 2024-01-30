/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_libft.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:28:42 by conobi            #+#    #+#             */
/*   Updated: 2021/12/08 17:32:26 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	f_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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
	n_write(1, s, f_strlen(s));
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

	base_len = f_strlen(base);
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
