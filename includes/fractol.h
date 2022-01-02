/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:40:18 by conobi            #+#    #+#             */
/*   Updated: 2022/01/02 17:23:52 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

/* structures */
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_pos {
	int		sx;
	int		sy;
	int		x;
	int		y;
}	t_pos;

typedef struct s_complex {
	float	x;
	float	y;
	float	ox;
	float	oy;
	float	a;
	float	b;
}	t_complex;

typedef struct s_context	t_context;

struct s_context {
	int		sx;
	int		sy;
	char	*command;
	short	(*fractal_func)(const t_pos, const t_context*);
	void	*mlx;
	void	*win;
	t_img	img;
	float	zoom;
	float	inzoom;
	float	midx;
	float	midy;
};

/* handlers.c */
t_img		handler(t_context *con);

/* utils.c */
void		pixel_put(t_img *data, int x, int y, int color);
t_pos		pos(int sx, int sy, int x, int y);
t_context	*set_func(t_context *con,
				short (*func)(const t_pos, const t_context*));
float		remap(float input, float low, float high);

/* rgba.c */
int			rgba2hex(int *color);
int			*hex2rgba(int color);
int			rgba(int r, int g, int b, int a);
int			generate(float t, int a, int b, int (*gen)(float, int, int, int));

/* colors.c */
int			gradient(float t, int a, int b, int chn);
int			linear(float t, int c, int d, int chn);

/* generators.c */
short		mandelbrot(const t_pos pos, const t_context *con);
short		julia(const t_pos pos, const t_context *con);
short		burning_ship(const t_pos pos, const t_context *con);

/* events.c */
void		event_listener(t_context *con);

#endif
