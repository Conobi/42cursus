/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:41:05 by conobi            #+#    #+#             */
/*   Updated: 2022/01/12 03:22:00 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_help(int argc, char **argv)
{
	if (argc == 1
		|| (argc > 1 && ft_strncmp(argv[1], "help", ft_strlen(argv[1]))))
		err_printer(22);
	printf("\e[92m\e[1mfractol\e[39m - A simple fractal visualizer\n\e[0m");
	printf("\n\e[92m\e[1mUSAGE:\e[0m\n\t%s \e[96m\e[4m[COMMAND]\e[0m", argv[0]);
	printf("\n\n\e[92m\e[1mCOMMANDS:\e[0m\n");
	printf("\t\e[96mjulia\e[0m - The julia set visualizer\n");
	printf("\t\e[96mmandelbrot\e[0m - The mandelbrot set visualizer\n");
	printf("\t\e[96mburning_ship\e[0m - The burning ship fractal visualizer\n");
	printf("\t\e[96mdebug\e[0m - For debugging simple commands without mlx\n");
	printf("\t\e[96mhelp\e[0m - To show this help\n\n");
}

static void	graph_manager(t_context *con)
{
	char	*win_name;

	con->mlx = mlx_init();
	con->zoom = 1;
	con->midx = 0.5;
	con->midy = 0.5;
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

	con.s.x = 800;
	con.s.y = 620;
	con.ox = 0.5;
	con.oy = 0.5;
	con.threads = 16;
	con.miters = 256;
	if (argc == 2)
		con.command = argv[1];
	if (argc == 2 && !ft_strncmp(argv[1], "julia", ft_strlen(argv[1])))
		graph_manager(set_func(&con, julia));
	else if (argc == 2
		&& !ft_strncmp(argv[1], "mandelbrot", ft_strlen(argv[1])))
		graph_manager(set_func(&con, mandelbrot));
	else if (argc == 2
		&& !ft_strncmp(argv[1], "burning_ship", ft_strlen(argv[1])))
		graph_manager(set_func(&con, burning_ship));
	else
		print_help(argc, argv);
	return (0);
}
