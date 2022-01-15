/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:02:59 by conobi            #+#    #+#             */
/*   Updated: 2022/01/15 19:37:24 by conobi           ###   ########lyon.fr   */
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

typedef struct s_palette {
	int			l;
	int			r;
	float		o;
}	t_palette;

typedef struct s_context	t_context;

struct s_context {
	t_palette		pal;
	t_vec2			s;
	t_img			img;
	pthread_mutex_t	lock;
	double long		zoom;
	double long		midx;
	double long		midy;
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

int	main(void)
{
	t_context	con;

	printf("%lu\n", sizeof(con.s));
}
