/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:33:25 by conobi            #+#    #+#             */
/*   Updated: 2021/12/13 17:27:14 by conobi           ###   ########lyon.fr   */
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

// static int	f_checkflow(long nb, short sign)
// {
// 	if (nb > 2147483648 || nb < -2147483649)
// 	{
// 		if (sign == 1)
// 			return (-1);
// 		return (0);
// 	}
// 	return ((int)nb * sign);
// }

// int	ft_atoi(const char *str)
// {
// 	int		sign;
// 	long	r;

// 	r = 0;
// 	while (*str == ' ' || (*str >= 9 && *str <= 13))
// 		str++;
// 	sign = 1;
// 	if (*str == '-')
// 	{
// 		sign = -1;
// 		str++;
// 	}
// 	else if (*str == '+')
// 		str++;
// 	while (ft_isdigit(*str))
// 	{
// 		r = r * 10 + *str - '0';
// 		str++;
// 	}
// 	return (f_checkflow(r, sign));
// }
