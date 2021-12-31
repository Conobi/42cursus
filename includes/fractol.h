/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:40:18 by conobi            #+#    #+#             */
/*   Updated: 2021/12/31 15:22:38 by conobi           ###   ########lyon.fr   */
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
typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_pos {
	int	sx;
	int	sy;
	int	x;
	int	y;
}	t_pos;

typedef struct s_complex {
	float	x;
	float	y;
	float	ox;
	float	oy;
	float	a;
	float	b;
}	t_complex;

/* handlers.c */
t_data	test_handler(void *mlx, int size_x, int size_y);
t_data	mandelbrot_handler(void *mlx, int size_x, int size_y);

/* utils.c */
void	pixel_put(t_data *data, int x, int y, int color);
t_pos	pos(int sx, int sy, int x, int y);

/* rgba.c */
int		rgba2hex(int *color);
int		*hex2rgba(int color);
int		rgba(int r, int g, int b, int a);
int		generate(float t, int a, int b, int (*gen)(float, int, int, int));

/* generators.c */
int		gradient(float t, int a, int b, int chn);
int		linear(float t, int c, int d, int chn);
int		mandelbrot(const t_pos pos, const float zoom);

#endif
