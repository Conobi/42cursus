/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:41:05 by conobi            #+#    #+#             */
/*   Updated: 2022/04/06 17:12:05 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_controls(void)
{
	printf("\n\e[92m\e[1mCONTROLS:\e[0m\n");
	printf("\t\e[93m[W,A,S,D, Dir arrows]\e[0m - Move the camera position\n");
	printf("\t\e[93m[Space]\e[0m - Reset the zoom and the camera position\n");
	printf("\t\e[93m[Numpad 1-6]\e[0m - Change the color palette\n");
	printf("\t\e[93m[Backspace]\e[0m - Lock/Unlock the color palette roller\n");
	printf("\t\e[93m[Numpad - +, Mouse wheel]\e[0m - Zoom/unzoom in the fractal\n");
	printf("\t\e[93m[Numpad / *,]\e[0m - Change the number of iterations\n");
	printf("\t\e[93m[Page up/down]\e[0m - Change the fractal resolution\n\n");
}

static void	print_help(int argc, char **argv)
{
	if (argc == 1
		|| (argc > 1 && ft_strncmp(argv[1], "help", ft_strlen(argv[1]))))
		err_printer(22);
	printf("\e[92m\e[1mfractol\e[39m - A simple fractal visualizer\n\e[0m");
	printf("\n\e[92m\e[1mUSAGE:\e[0m\n\t%s \e[96m\e[4m[COMMAND]\e[0m", argv[0]);
	printf("\n\n\e[92m\e[1mCOMMANDS:\e[0m\n");
	printf("\t\e[96mjulia [x param] [y param]\e[0m - The julia set visualizer\n");
	printf("\t\e[96mmandelbrot\e[0m - The mandelbrot set visualizer\n");
	printf("\t\e[96mburning_ship\e[0m - The burning ship fractal visualizer\n");
	printf("\t\e[96meagle_brain\e[0m - The eagle brain fractal visualizer\n");
	printf("\t\e[96mbaobab\e[0m - The baobab fractal visualizer\n");
	printf("\t\e[96mwobble\e[0m - The wobble fractal visualizer\n");
	printf("\t\e[96mhelp\e[0m - To show this help\n");
	print_controls();
}

static void	context_init(t_context *con)
{
	con->threads = 16;
	con->miters = 128;
	con->res = 2;
	con->s.x = 1080 - 1080 % con->threads;
	con->s.y = 720;
	con->zoom = 1;
	con->midx = 0.5;
	con->midy = 0.5;
	con->ox = 0.5;
	con->oy = 0.5;
	con->pznum = 1;
	con->pzdir = -1;
	con->pzlock = 1;
	con->holock = -1;
	palette_set(con, con->func_i);
}

static void	graph_manager(t_context *con)
{
	char	*win_name;

	context_init(con);
	con->mlx = mlx_init();
	win_name = ft_strjoin("Fractol - ", con->command);
	if (!win_name)
		return ;
	con->win = mlx_new_window(con->mlx, con->s.x, con->s.y, win_name);
	con->img = thread_handler(con);
	mlx_put_image_to_window(con->mlx, con->win, con->img.img, 0, 0);
	event_listener(con);
	mlx_loop(con->mlx);
	free(win_name);
}

int	main(int argc, char **argv)
{
	t_context	con;

	if (argc == 2 || argc == 4)
		con.command = argv[1];
	cli_parser(argc, argv, &con);
	if (argc == 4 && !ft_strncmp("julia", argv[1], 5))
		graph_manager(set_func(0, &con, julia));
	else if (argc == 2
		&& !ft_strncmp("mandelbrot", argv[1], 10))
		graph_manager(set_func(1, &con, mandelbrot));
	else if (argc == 2
		&& !ft_strncmp("burning_ship", argv[1], 12))
		graph_manager(set_func(2, &con, burning_ship));
	else if (argc == 2
		&& !ft_strncmp("eagle_brain", argv[1], 11))
		graph_manager(set_func(3, &con, eagle_brain));
	else if (argc == 2
		&& !ft_strncmp("baobab", argv[1], 6))
		graph_manager(set_func(4, &con, baobab));
	else if (argc == 2
		&& !ft_strncmp("wobble", argv[1], 6))
		graph_manager(set_func(5, &con, wobble));
	else
		print_help(argc, argv);
	return (0);
}
