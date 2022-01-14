/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:40:18 by conobi            #+#    #+#             */
/*   Updated: 2022/01/14 18:59:28 by conobi           ###   ########lyon.fr   */
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

typedef struct s_chunk {
	t_vec2		s;
	t_vec2		e;
}	t_chunk;

typedef struct s_palette {
	int			l;
	int			r;
	float		o;
}	t_palette;

typedef struct s_context	t_context;

struct s_context {
	float			(*fractal_func)(const t_pos, const t_context*);
	char			*command;
	int				func_i;
	t_vec2			s;
	t_img			img;
	t_chunk			chk;
	t_palette		pal;
	pthread_mutex_t	lock;
	int				threads;
	int				miters;
	int				res;
	int				currthr;
	double long		zoom;
	float			pznum;
	short			pzdir;
	short			pzlock;
	double long		midx;
	double long		midy;
	void			*mlx;
	void			*win;
	float			ox;
	float			oy;
	float			cox;
	float			coy;
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
t_chunk		chunk(t_vec2 s, t_vec2 e, t_context *con);

/* utils.c */
void		err_printer(int err);
void		err_ender(int err);
void		info_printer(char *note);
int			ender(void);

/* rgba.c */
int			rgba2hex(t_rgba color);
t_rgba		hex2rgba(int color);
int			rgba(int r, int g, int b, int a);
int			generate(double t, t_context *con,
				int (*gen)(double long, int, int, int));

/* colors.c */
int			gradient(double long t, int a, int b, int chn);
int			linear(double long t, int c, int d, int chn);
void		palette_set(t_context *con, int index);

/* generators.c */
float		mandelbrot(const t_pos pos, const t_context *con);
float		julia(const t_pos pos, const t_context *con);
float		burning_ship(const t_pos pos, const t_context *con);
float		gradlr(const t_pos pos, const t_context *con);

/* events.c */
void		event_listener(t_context *con);

/* events_handlers.c */
void		zoom_mouse(int btn, int x, int y, t_context *con);
void		zoom_move_reset(int key, t_context *con);
void		space_debug(int key, t_context *con);
void		palette_change(int key, t_context *con);
void		palette_locker(int key, t_context *con);
void		resol_change(int key, t_context *con);

#endif
