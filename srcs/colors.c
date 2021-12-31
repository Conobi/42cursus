/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 19:02:13 by conobi            #+#    #+#             */
/*   Updated: 2021/12/31 19:02:28 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	gradient(float t, int a, int b, int chn)
{
	int	ret;
	int	color_a[4];
	int	color_b[4];

	ft_arrlcpy(color_a, hex2rgba(a), 3);
	ft_arrlcpy(color_b, hex2rgba(b), 3);
	ret = (color_a[chn] - color_b[chn]) * t + color_b[chn];
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
