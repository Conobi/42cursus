/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:33:25 by conobi            #+#    #+#             */
/*   Updated: 2022/04/06 18:15:58 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_max(long nb, int sign)
{
	if (nb * sign > 2147483647)
		return (-1);
	if (nb * sign < -2147483648)
		return (0);
	return (nb * sign);
}

int	ft_atoi(char const *str)
{
	int				sign;
	unsigned long	res;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			res *= 10;
			res += *(str++) - '0';
		}
		else
			return (res * sign);
	}
	return (ft_check_max(res, sign));
}
