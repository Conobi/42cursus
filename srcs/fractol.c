/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:41:05 by conobi            #+#    #+#             */
/*   Updated: 2021/12/28 17:07:49 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_help(int argc, char **argv)
{
	if (argc == 1
		|| (argc > 1 && ft_strncmp(argv[1], "help", ft_strlen(argv[1]))))
		printf("\e[91m\e[1m\e[4mError:\e[0m %s.\n", strerror(22));
	printf("\e[92m\e[1mfractol\e[39m - A simple fractal visualizer\n\e[0m");
	printf("\n\e[92m\e[1mUSAGE:\e[0m\n\tfractol \e[96m\e[4m[COMMAND]\e[0m");
	printf("\n\n\e[92m\e[1mCOMMANDS:\e[0m\n");
	printf("\t\e[96mtest\e[0m - A simple test handler\n");
	printf("\t\e[96mhelp\e[0m - To show this help\n\n");
}

int	main(int argc, char **argv)
{
	if (argc == 2 && !ft_strncmp(argv[1], "test", ft_strlen(argv[1])))
		test_handler();
	else
		print_help(argc, argv);
	return (0);
}
