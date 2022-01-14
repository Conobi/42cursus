/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:23:09 by conobi            #+#    #+#             */
/*   Updated: 2022/01/14 18:58:41 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	*thread_cutter(void *args)
{
	int			color;
	t_context	*con;
	float		t;
	t_vec2		s;
	t_vec2		e;

	con = (t_context *)args;
	pthread_mutex_lock(&con->lock);
	--con->currthr;
	s = (t_vec2){con->s.x / con->threads * (con->currthr), 0};
	e = (t_vec2){con->s.x / con->threads * (con->currthr + 1), con->s.y};
	pthread_mutex_unlock(&con->lock);
	while (s.x < e.x)
	{
		s.y = 0;
		while (s.y < e.y)
		{
			t = con->fractal_func(pos(con->s.x, con->s.y, s.x, s.y), con);
			color = generate(t, con, &linear);
			pixel_put(con, s.x, s.y, color);
			s.y += con->res;
		}
		s.x += con->res;
	}
	return (0);
}

t_img	thread_handler(t_context *con)
{
	pthread_t	*tid;
	int			i;
	int			stat;

	i = -1;
	con->currthr = con->threads;
	tid = ft_calloc(con->threads, sizeof(pthread_t));
	con->img.img = mlx_new_image(con->mlx, con->s.x, con->s.y);
	con->img.addr = mlx_get_data_addr(con->img.img, &con->img.bits_per_pixel,
			&con->img.line_length, &con->img.endian);
	stat = pthread_mutex_init(&con->lock, NULL);
	if (stat != 0)
		err_ender(stat);
	while (++i < con->threads)
	{
		stat = pthread_create(&(tid[i]), NULL, thread_cutter, con);
		if (stat != 0)
			err_ender(stat);
	}
	i = -1;
	while (++i < con->threads)
		pthread_join(tid[i], NULL);
	pthread_mutex_destroy(&con->lock);
	free(tid);
	return (con->img);
}

void	refresh_handler(t_context *con)
{
	mlx_destroy_image(con->mlx, con->img.img);
	con->img = thread_handler(con);
	mlx_put_image_to_window(con->mlx, con->win, con->img.img, 0, 0);
}
