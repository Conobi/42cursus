/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:36:43 by conobi            #+#    #+#             */
/*   Updated: 2021/11/16 20:21:45 by conobi           ###   ########lyon.fr   */
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
