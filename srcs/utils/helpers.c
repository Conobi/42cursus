/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:33:52 by conobi            #+#    #+#             */
/*   Updated: 2022/10/20 17:21:06 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_tmp{
	t_img	upscaled;
	char	*dst;
	int		x;
	int		y;
	int		xx;
	int		yy;
	int		draw_x;
	int		draw_y;
	int		color;
}	t_tmp;

void	pixel_put(t_ctx *c, int x, int y, int color)
{
	char	*dst;

	dst = NULL;
	if (y >= 0 && x >= 0 && y < c->window.height && x < c->window.width)
	{
		dst = c->img.addr + (y * c->img.line_length
				+ x * (c->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

double long	remap(double long input, double long low, double long high)
{
	double long	ret;

	ret = low + input * (high - low);
	return (ret);
}

static void	upscale_image(t_ctx *c, t_tmp *t)
{
	t->yy = 0;
	t->color = get_pixel_color_from_texture(c->img,
			t->x, t->y);
	while (t->yy < c->window.res)
	{
		t->xx = 0;
		while (t->xx < c->window.res)
		{
			if (t->yy >= 0 && t->xx >= 0
				&& t->yy < c->window.height * c->window.res
				&& t->xx < c->window.width * c->window.res)
			{
				t->dst = t->upscaled.addr
					+ ((t->draw_y + t->yy) * t->upscaled.line_length
						+ (t->draw_x + t->xx)
						* (t->upscaled.bits_per_pixel / 8));
				*(unsigned int *)t->dst = t->color;
			}
			t->xx++;
		}
		t->yy++;
	}
	t->x++;
}

void	upscale(t_ctx *c)
{
	t_tmp	t;

	t.upscaled.img = mlx_new_image(c->window.mlx,
			c->window.width * c->window.res, c->window.height * c->window.res);
	t.upscaled.addr = mlx_get_data_addr(t.upscaled.img,
			&t.upscaled.bits_per_pixel,
			&t.upscaled.line_length, &t.upscaled.endian);
	t.y = 0;
	t.draw_y = 0;
	c->img.width = c->window.width;
	c->img.height = c->window.height;
	while (t.y < c->window.height)
	{
		t.x = 0;
		t.draw_x = 0;
		while (t.x < c->window.width)
		{
			upscale_image(c, &t);
			t.draw_x += c->window.res;
		}
		t.draw_y += c->window.res;
		t.y++;
	}
	mlx_destroy_image(c->window.mlx, c->img.img);
	c->img = t.upscaled;
}
