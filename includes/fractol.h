/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:40:18 by conobi            #+#    #+#             */
/*   Updated: 2022/04/06 17:11:43 by conobi           ###   ########lyon.fr   */
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
# include <time.h>

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

typedef struct s_palette {
	int			l;
	int			r;
	float		o;
}	t_palette;

typedef struct s_context	t_context;

struct s_context {
	pthread_mutex_t	lock;
	t_palette		pal;
	double long		zoom;
	double long		midx;
	double long		midy;
	t_img			img;
	t_vec2			s;
	float			(*fractal_func)(const t_pos, const t_context*);
	void			*mlx;
	void			*win;
	char			*command;
	int				func_i;
	int				threads;
	int				miters;
	int				res;
	int				currthr;
	float			ox;
	float			oy;
	float			cox;
	float			coy;
	float			pznum;
	short			pzdir;
	short			pzlock;
	short			holock;
};

/* handlers.c */
t_img		thread_handler(t_context *con);
void		refresh_handler(t_context *con);

/* helpers.c */
void		pixel_put(t_context *con, int x, int y, int color);
t_pos		pos(int sx, int sy, int x, int y);
t_context	*set_func(int func_i, t_context *con,
				float (*func)(const t_pos, const t_context*));
double long	remap(double long input, double long low, double long high);

/* utils.c */
void		err_printer(int err);
void		err_ender(int err);
void		info_printer(char *note);
void		cli_parser(int argc, char **argv, t_context *con);
int			ender(void);

/* colors.c */
int			rgba2hex(t_rgba color);
t_rgba		hex2rgba(int color);
int			generate(double t, t_context *con,
				int (*gen)(double long, int, int, int));
int			linear(double long t, int c, int d, int chn);
void		palette_set(t_context *con, int index);

/* generators.c */
float		mandelbrot(const t_pos pos, const t_context *con);
float		julia(const t_pos pos, const t_context *con);
float		toast(const t_pos pos, const t_context *con);
float		gradlr(const t_pos pos, const t_context *con);

/* bonus_generators.c */
float		burning_ship(const t_pos pos, const t_context *con);
float		eagle_brain(const t_pos pos, const t_context *con);
float		baobab(const t_pos pos, const t_context *con);
float		wobble(const t_pos pos, const t_context *con);

/* events.c */
void		event_listener(t_context *con);

/* events_handlers.c */
void		zoom_move_reset(int key, t_context *con);
void		palette_change(int key, t_context *con);
void		lockers(int key, t_context *con);
void		resol_iter_change(int key, t_context *con);

#endif
