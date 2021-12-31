/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:41:05 by conobi            #+#    #+#             */
/*   Updated: 2021/12/31 15:36:37 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_help(int argc, char **argv)
{
	if (argc == 1
		|| (argc > 1 && ft_strncmp(argv[1], "help", ft_strlen(argv[1]))))
		printf("\e[91m\e[1m\e[4mError:\e[0m %s.\n", strerror(22));
	printf("\e[92m\e[1mfractol\e[39m - A simple fractal visualizer\n\e[0m");
	printf("\n\e[92m\e[1mUSAGE:\e[0m\n\t%s \e[96m\e[4m[COMMAND]\e[0m", argv[0]);
	printf("\n\n\e[92m\e[1mCOMMANDS:\e[0m\n");
	printf("\t\e[96mmandelbrot\e[0m - The mandelbrot set visualizer\n");
	printf("\t\e[96mtest\e[0m - A simple test handler\n");
	printf("\t\e[96mdebug\e[0m - For debugging simple commands without mlx\n");
	printf("\t\e[96mhelp\e[0m - To show this help\n\n");
}

static void	graph_manager(int sx, int sy, t_data (*handler)(void *, int, int))
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, sx, sy, "Fractol");
	img = (*handler)(mlx, sx, sy);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

int	main(int argc, char **argv)
{
	int	sx;
	int	sy;
	int	*color;

	sx = 1280;
	sy = 720;
	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", ft_strlen(argv[1])))
		graph_manager(sx, sy, &mandelbrot_handler);
	else if (argc == 2 && !ft_strncmp(argv[1], "test", ft_strlen(argv[1])))
		graph_manager(sx, sy, &test_handler);
	else if (argc == 2 && !ft_strncmp(argv[1], "debug", ft_strlen(argv[1])))
	{
		color = hex2rgba(rgba(127, 50, 63, 255));
		printf("Hexa: %x\n", rgba2hex(color));
		printf("rgba(%d, %d, %d, %d)\n", color[0], color[1], color[2], color[3]);
	}
	else
		print_help(argc, argv);
	return (0);
}
