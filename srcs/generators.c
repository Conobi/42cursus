/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:38:01 by conobi            #+#    #+#             */
/*   Updated: 2021/12/30 02:42:00 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	gradient(float t, int a, int b, char chn)
{
	int		ret;
	t_rgba	color_a;
	t_rgba	color_b;

	color_a = hex2rgba(a);
	color_b = hex2rgba(b);
	if (chn == 'r')
		ret = (color_a.r - color_b.r) * t + color_b.r;
	else if (chn == 'g')
		ret = (color_a.g - color_b.g) * t + color_b.g;
	else if (chn == 'b')
		ret = (color_a.b - color_b.b) * t + color_b.b;
	else
		ret = (color_a.a - color_b.a) * t + color_b.a;
	return (ret);
}
