/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:04:59 by conobi            #+#    #+#             */
/*   Updated: 2022/10/20 16:10:45 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgba2hex(t_rgba color)
{
	return ((255 - color.alpha) << 24 | color.red << 16
		| color.green << 8 | color.blue);
}

t_rgba	hex2rgba(int color)
{
	t_rgba	ret;

	ret.alpha = ((color >> 24) & 0xff) + 255;
	ret.red = (color >> 16) & 0xff;
	ret.green = (color >> 8) & 0xff;
	ret.blue = color & 0xff;
	return (ret);
}

static t_rgba	srgb_companding(t_rgba color)
{
	double	r;
	double	g;
	double	b;

	r = (double)color.red / 255;
	g = (double)color.green / 255;
	b = (double)color.blue / 255;
	if (r > 0.0031308)
		r = 1.055 * pow(r, 1 / 2.4) - 0.055;
	else
		r = r * 12.92;
	if (g > 0.0031308)
		g = 1.055 * pow(g, 1 / 2.4) - 0.055;
	else
		g = g * 12.92;
	if (b > 0.0031308)
		b = 1.055 * pow(b, 1 / 2.4) - 0.055;
	else
		b = b * 12.92;
	return ((t_rgba){(int)(r * 255), (int)(g * 255), (int)(b * 255), 0});
}

static t_rgba	rev_srgb_companding(t_rgba color)
{
	double	r;
	double	g;
	double	b;

	r = (double)color.red / 255;
	g = (double)color.green / 255;
	b = (double)color.blue / 255;
	if (r > 0.04045)
		r = pow((r + 0.055) / 1.055, 2.4);
	else
		r = r / 12.92;
	if (g > 0.04045)
		g = pow((g + 0.055) / 1.055, 2.4);
	else
		g = g / 12.92;
	if (b > 0.04045)
		b = pow((b + 0.055) / 1.055, 2.4);
	else
		b = b / 12.92;
	return ((t_rgba){(int)(r * 255), (int)(g * 255), (int)(b * 255), 0});
}

// Step [0..1]
//  0   --> all from
//  0.5 --> equal step of from and to
//  1   --> all to
int	linear_gradient(int from, int to, float step, bool srgb)
{
	t_rgba	from_rgba;
	t_rgba	to_rgba;
	t_rgba	ret;

	from_rgba = hex2rgba(from);
	to_rgba = hex2rgba(to);
	if (step > 1)
		step = 1;
	else if (step < 0)
		step = 0;
	if (srgb)
	{
		from_rgba = rev_srgb_companding(from_rgba);
		to_rgba = rev_srgb_companding(to_rgba);
	}
	ret.red = from_rgba.red * (1 - step) + to_rgba.red * step;
	ret.green = from_rgba.green * (1 - step) + to_rgba.green * step;
	ret.blue = from_rgba.blue * (1 - step) + to_rgba.blue * step;
	if (srgb)
		ret = srgb_companding(ret);
	ret.alpha = 255;
	return (rgba2hex(ret));
}
