/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:02:59 by conobi            #+#    #+#             */
/*   Updated: 2022/01/14 15:14:07 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/opengl/mlx.h"
#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

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
	int				upsc;
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

typedef struct s_vars {
	void	*mlx;
	void	*win;
}	t_vars;

int	key_hook(int button, int x, int y, t_context *con)
{
	printf("Hello %d from (%d, %d)\n", button, x, y);
	return (0);
}

int	main(void)
{
	t_context	con;

	con.mlx = mlx_init();
	con.win = mlx_new_window(con.mlx, 1080, 720, "Hello world!");
	mlx_mouse_hook(con.win, key_hook, &con);
	mlx_loop(con.mlx);
}
