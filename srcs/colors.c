/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 19:02:13 by conobi            #+#    #+#             */
/*   Updated: 2022/01/11 00:12:27 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	gradient(double long t, int a, int b, int chn)
{
	int	ret;

	ret = (hex2rgba(a).arr[chn] - hex2rgba(b).arr[chn])
		* t + hex2rgba(b).arr[chn];
	return (ret);
}

int	linear(double long t, int c, int d, int chn)
{
	double long	ret;

	ret = (double long)(hex2rgba(c).arr[chn]) / 255 * t;
	ret += (double long)(hex2rgba(d).arr[chn]) / 255;
	ret = (0.5 + 0.5 * cos(6.28318 * ret)) * 255;
	return ((int)ret);
}
