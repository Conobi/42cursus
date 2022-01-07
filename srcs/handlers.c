/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:23:09 by conobi            #+#    #+#             */
/*   Updated: 2022/01/05 19:42:53 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_img	handler(t_context *con)
{
	float	t;
	t_img	img;
	int		isx;
	int		isy;
	int		color;

	img.img = mlx_new_image(con->mlx, con->s.x, con->s.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	isx = con->s.x;
	con->zoom = remap(con->inzoom, 0.005, 1.8);
	while (--isx >= 0)
	{
		isy = con->s.y;
		while (--isy >= 0)
		{
			t = (float)con->fractal_func(
					pos(con->s.x, con->s.y, isx, isy), con) / 255;
			color = generate(t - 0.59, 0xFFFFFF, 0x001933, &linear);
			pixel_put(&img, isx, isy, color);
		}
	}
	return (img);
}

void	*thread_cutter(void *args)
{
	t_context	*con;
	t_vec2		s;
	t_vec2		e;
	float		t;
	int			color;

	con = (t_context *)args;
	pthread_mutex_lock(&con->lock);
	--con->currthr;
	s = vec2(con->s.x / con->threads * con->currthr, 0);
	e = vec2(con->s.x / con->threads * (con->currthr + 1), con->s.y);
	pthread_mutex_unlock(&con->lock);
	--s.x;
	while (++s.x < e.x)
	{
		s.y = -1;
		while (++s.y < e.y)
		{
			t = (float)con->fractal_func(
					pos(con->s.x, con->s.y,
						s.x, s.y), con) / 128;
			color = generate(t - 0.59, 0xFFFFFF, 0x001933, &linear);
			pixel_put(&con->img, s.x, s.y, color);
		}
	}
	return (con);
}

t_img	thread_handler(t_context *con)
{
	int			i;
	pthread_t	*tid;

	i = -1;
	con->currthr = con->threads;
	tid = ft_calloc(con->threads, sizeof(pthread_t));
	con->img.img = mlx_new_image(con->mlx, con->s.x, con->s.y);
	con->img.addr = mlx_get_data_addr(con->img.img, &con->img.bits_per_pixel,
			&con->img.line_length, &con->img.endian);
	con->zoom = remap(con->inzoom, 0.005, 1.8);
	if (pthread_mutex_init(&con->lock, NULL) != 0)
	{
		printf("\nMutex init failed\n");
		exit(1);
	}
	while (++i < con->threads)
		pthread_create(&(tid[i]), NULL, thread_cutter, con);
	i = -1;
	while (++i < con->threads)
		pthread_join(tid[i], NULL);
	pthread_mutex_destroy(&con->lock);
	free(tid);
	return (con->img);
}

// t_data	test_handler(void *mlx, int size_x, int size_y)
// {
// 	t_data	img;
// 	int		isx;
// 	int		isy;
// 	double	t;
// 	int		pixel;

// 	img.img = mlx_new_image(mlx, size_x, size_y);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 			&img.endian);
// 	isx = size_x;
// 	while (--isx >= 0)
// 	{
// 		isy = size_y;
// 		while (--isy >= 0)
// 		{
// 			t = (double)isx / (double)size_x;
// 			pixel = generate(t, 0xFFFFFF, 0x001933, &linear);
// 			pixel_put(&img, isx, isy, pixel);
// 		}
// 	}
// 	printf("\e[92m\e[1mDone\e[0m\n");
// 	return (img);
// }

//	color = generate(t, 0xFFFFFF, 0x001933, &linear);
//	color = generate(t, 0xFFFFFF, 0x0054aa, &linear);
// color = generate(t - 1, 0x7f7f7f, 0x7f333f, &linear);
// Burning:
// color = generate(t - 0.03, 0x10FF00, 0xFF54aa, &linear);


	// while (--bite >= 0)
	// {
	// 	// thread_cutter(&chunk[threads]);
	// 	pthread_create(&tid, NULL, thread_cutter, &chunk[bite]);
	// 	// printf("%d: %p\n", threads, chunk->tid);
	// }
	// exit(0);
	// pthread_exit(NULL);
	// thread_cutter(, vec2(dsizex * 1, con->s.y), con);
	// thread_cutter(vec2(con->s.x - dsizex * 3, 0), vec2(dsizex * 2, con->s.y), con);
	// thread_cutter(vec2(con->s.x - dsizex * 2, 0), vec2(dsizex * 3, con->s.y), con);
	// thread_cutter(vec2(con->s.x - dsizex * 1, 0), vec2(dsizex * 4, con->s.y), con);

