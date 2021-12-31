/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:41:05 by conobi            #+#    #+#             */
/*   Updated: 2021/12/31 21:15:43 by conobi           ###   ########lyon.fr   */
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
	printf("\t\e[96mjulia\e[0m - The julia set visualizer\n");
	printf("\t\e[96mmandelbrot\e[0m - The mandelbrot set visualizer\n");
	printf("\t\e[96mburning_ship\e[0m - The burning ship fractal visualizer\n");
	printf("\t\e[96mdebug\e[0m - For debugging simple commands without mlx\n");
	printf("\t\e[96mhelp\e[0m - To show this help\n\n");
}

static void	graph_manager(t_context con, short (*fractal)(t_pos, float))
{
	char	*win_name;
	void	*mlx_win;
	t_data	img;

	con.mlx = mlx_init();
	win_name = ft_strjoin("Fractol - ", con.command);
	if (!win_name)
		return ;
	mlx_win = mlx_new_window(con.mlx, con.sx, con.sy, win_name);
	img = handler(con, fractal);
	mlx_put_image_to_window(con.mlx, mlx_win, img.img, 0, 0);
	mlx_loop(con.mlx);
	free(win_name);
}

int	main(int argc, char **argv)
{
	t_context	con;
	int			*color;

	con.sx = 1280;
	con.sy = 720;
	if (argc == 2)
		con.command = argv[1];
	if (argc == 2 && !ft_strncmp(argv[1], "julia", ft_strlen(argv[1])))
		graph_manager(con, &julia);
	else if (argc == 2
		&& !ft_strncmp(argv[1], "mandelbrot", ft_strlen(argv[1])))
		graph_manager(con, &mandelbrot);
	else if (argc == 2
		&& !ft_strncmp(argv[1], "burning_ship", ft_strlen(argv[1])))
		graph_manager(con, &burning_ship);
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
