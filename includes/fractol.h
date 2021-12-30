/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:40:18 by conobi            #+#    #+#             */
/*   Updated: 2021/12/29 16:21:02 by conobi           ###   ########lyon.fr   */
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

typedef struct s_rgba {
	int	r;
	int	g;
	int	b;
	int	a;
}	t_rgba;

/* handlers.c */
t_data	test_handler(void *mlx, int size_x, int size_y);

/* utils.c */
void	pixel_put(t_data *data, int x, int y, int color);
int		interpolate(int color1, int color2, float fraction);

/* rgba.c */
int		rgba2hex(t_rgba color);
t_rgba	hex2rgba(int color);
int		rgba(int r, int g, int b, int a);
int		generate(float t, int a, int b, int (*gen)(float, int, int, char));

/* generators.c */
int		gradient(float t, int a, int b, char chn);

#endif
