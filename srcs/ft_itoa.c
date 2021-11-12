/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:14:52 by conobi            #+#    #+#             */
/*   Updated: 2021/11/12 15:52:00 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	f_dec_count(int n)
{
	int	cnt;

	cnt = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		sign;
	int		len;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = f_dec_count(n) + sign;
	ret = ft_calloc((len + 1), sizeof(*ret));
	if (!ret)
		return (NULL);
	ret[len--] = '\0';
	if (n == 0)
		ret[len] = 48;
	while (n != 0)
	{
		if (sign)
			ret[len--] = 48 + n % 10 * -1;
		else
			ret[len--] = 48 + n % 10;
		n /= 10;
	}
	if (sign)
		ret[len] = '-';
	return (ret);
}
