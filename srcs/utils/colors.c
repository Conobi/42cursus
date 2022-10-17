/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:04:59 by conobi            #+#    #+#             */
/*   Updated: 2022/10/14 19:29:09 by conobi           ###   ########lyon.fr   */
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

// static t_rgba	srgb_companding(t_rgba color)
// {
// 	double	r;
// 	double	g;
// 	double	b;

// 	r = (double)color.red / 255;
// 	g = (double)color.green / 255;
// 	b = (double)color.blue / 255;
// 	if (r > 0.0031308)
// 		r = 1.055 * pow(r, 1 / 2.4) - 0.055;
// 	else
// 		r = r * 12.92;
// 	if (g > 0.0031308)
// 		g = 1.055 * pow(g, 1 / 2.4) - 0.055;
// 	else
// 		g = g * 12.92;
// 	if (b > 0.0031308)
// 		b = 1.055 * pow(b, 1 / 2.4) - 0.055;
// 	else
// 		b = b * 12.92;
// 	// printf("%d, %d, %d\n", (int)(r * 255), (int)(g * 255), (int)(b * 255));
// 	return ((t_rgba){(int)(r * 255), (int)(g * 255), (int)(b * 255), 0});
// }

// static t_rgba	rev_srgb_companding(t_rgba color)
// {
// 	double	r;
// 	double	g;
// 	double	b;

// 	r = (double)color.red / 255;
// 	g = (double)color.green / 255;
// 	b = (double)color.blue / 255;
// 	if (r > 0.04045)
// 		r = pow((r + 0.055) / 1.055, 2.4);
// 	else
// 		r = r / 12.92;
// 	if (g > 0.04045)
// 		g = pow((g + 0.055) / 1.055, 2.4);
// 	else
// 		g = g / 12.92;
// 	if (b > 0.04045)
// 		b = pow((b + 0.055) / 1.055, 2.4);
// 	else
// 		b = b / 12.92;
// 	// printf("%d, %d, %d\n", (int)(r * 255), (int)(g * 255), (int)(b * 255));
// 	return ((t_rgba){(int)(r * 255), (int)(g * 255), (int)(b * 255), 0});
// }

// Step [0..1]
//  0   --> all from
//  0.5 --> equal step of from and to
//  1   --> all to
t_rgba	linear_gradient(t_rgba from, t_rgba to, float step)
{
	t_rgba	ret;

	if (step > 1)
		step = 1;
	else if (step < 0)
		step = 0;
	// from = rev_srgb_companding(from);
	// to = rev_srgb_companding(to);
	ret.red = from.red * (1 - step) + to.red * step;
	ret.green = from.green * (1 - step) + to.green * step;
	ret.blue = from.blue * (1 - step) + to.blue * step;
	// ret = srgb_companding(ret);
	ret.alpha = 255;
	// printf("%d, %d, %d\n", ret.red, ret.green, ret.blue);
	return (ret);
}
