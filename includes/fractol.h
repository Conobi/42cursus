/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:40:18 by conobi            #+#    #+#             */
/*   Updated: 2022/01/11 00:26:33 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include "libft.h"
# include "keys.h"
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>

/* structures */
typedef struct s_vec2 {
	int	x;
	int	y;
}	t_vec2;

typedef struct s_rgba {
	int	arr[4];
}	t_rgba;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_pos {
	t_vec2	s;
	t_vec2	i;
}	t_pos;

typedef struct s_complex {
	double long	x;
	double long	y;
	double long	ox;
	double long	oy;
	double long	a;
	double long	b;
}	t_complex;

typedef struct s_chunk {
	t_vec2		s;
	t_vec2		e;
}	t_chunk;

typedef struct s_context	t_context;

struct s_context {
	t_vec2			s;
	t_img			img;
	t_chunk			chk;
	pthread_mutex_t	lock;
	int				currthr;
	short			(*fractal_func)(const t_pos, const t_context*);
	char			*command;
	void			*mlx;
	void			*win;
	double long		zoom;
	double long		inzoom;
	double long		midx;
	double long		midy;
	int				threads;
};

/* handlers.c */
t_img		handler(t_context *con);
t_img		thread_handler(t_context *con);

/* utils.c */
void		pixel_put(t_img *data, int x, int y, int color);
t_pos		pos(int sx, int sy, int x, int y);
t_context	*set_func(t_context *con,
				short (*func)(const t_pos, const t_context*));
double long	remap(double long input, double long low, double long high);
t_vec2		vec2(int x, int y);
t_chunk		chunk(t_vec2 s, t_vec2 e, t_context *con);

/* rgba.c */
int			rgba2hex(t_rgba color);
t_rgba		hex2rgba(int color);
int			rgba(int r, int g, int b, int a);
int			generate(double t, int a, int b,
				int (*gen)(double long, int, int, int));

/* colors.c */
int			gradient(double long t, int a, int b, int chn);
int			linear(double long t, int c, int d, int chn);

/* generators.c */
short		mandelbrot(const t_pos pos, const t_context *con);
short		julia(const t_pos pos, const t_context *con);
short		burning_ship(const t_pos pos, const t_context *con);

/* events.c */
void		event_listener(t_context *con);

#endif
