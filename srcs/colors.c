/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 19:02:13 by conobi            #+#    #+#             */
/*   Updated: 2022/01/05 20:02:58 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	gradient(float t, int a, int b, int chn)
{
	int	ret;

	ret = (hex2rgba(a)[chn] - hex2rgba(b)[chn]) * t + hex2rgba(b)[chn];
	return (ret);
}

int	linear(float t, int c, int d, int chn)
{
	float	ret;

	ret = (float)(hex2rgba(c)[chn]) / 255 * t;
	ret += (float)(hex2rgba(d)[chn]) / 255;
	ret = (0.5 + 0.5 * cos(6.28318 * ret)) * 255;
	return ((int)ret);
}
