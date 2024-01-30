/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:30:51 by conobi            #+#    #+#             */
/*   Updated: 2022/04/06 15:22:29 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	comma(char **s, int *e, double *a)
{
	if (**s == '.')
	{
		*s = *s + 1;
		while (**s && ft_isdigit(**s))
		{
			*a = *a * 10.0 + (**s - '0');
			*e -= 1;
			*s += 1;
		}
	}
	while (*e < 0)
	{
		*a *= 0.1;
		*e = *e + 1;
	}
}

double	ft_atof(char *s)
{
	double	a;
	int		e;
	int		sign;

	a = 0.0;
	e = 0;
	sign = 1;
	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		s++;
		sign = -1;
	}
	while (*s && ft_isdigit(*s))
	{
		a = a * 10.0 + (*s - '0');
		s++;
	}
	comma(&s, &e, &a);
	return (a * sign);
}
