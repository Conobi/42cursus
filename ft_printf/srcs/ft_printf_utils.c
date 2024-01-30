/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:36:43 by conobi            #+#    #+#             */
/*   Updated: 2021/12/08 17:30:13 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	counter(int n)
{
	static int	cnt;

	if (n == -1)
		cnt = 0;
	else
		cnt += n;
	return (cnt);
}

size_t	n_write(int fd, const void *buf, size_t n)
{
	size_t	ret;

	ret = write(fd, buf, n);
	if ((int)ret != -1)
		counter(n);
	return (ret);
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
