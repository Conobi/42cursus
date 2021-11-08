/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:16:40 by conobi            #+#    #+#             */
/*   Updated: 2021/11/08 16:20:34 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkflow(long nb, short sign)
{
	if (nb > 2147483648 || nb < -2147483649)
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	return ((int)nb * sign);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	r;

	r = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		r = r * 10 + *str - '0';
		str++;
	}
	return (ft_checkflow(r, sign));
}

/*
	if (*str == '-' || *str == '+')
		sign = 1 - 2 * (*str++ == '-');
*/
