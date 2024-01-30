/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:47:54 by abastos           #+#    #+#             */
/*   Updated: 2022/10/20 18:07:13 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	print_help(char **argv)
{
	printf("\e[92m\e[1mcub3D\e[39m - A 3D map explorer\n\e[0m");
	printf("\n\e[92m\e[1mUSAGE:\e[0m\n\t%s", argv[0]);
	printf(" \e[96m\e[4m[your map file with its path]\e[0m\n\n");
	return (0);
}

static void	graph_manager(t_ctx *c)
{
	c->window.id = mlx_new_window(c->window.mlx,
			c->window.width * c->window.res,
			c->window.height * c->window.res, "cub3d");
	c->img = image_handler(c);
	c->hitbox_max = c->cell_size * 0.25;
	c->target_speed = c->cell_size * 0.15;
	mlx_put_image_to_window(c->window.mlx, c->window.id, c->img.img, 0, 0);
	event_listener(c);
	mlx_mouse_hide(c->window.mlx, c->window.id);
	mlx_loop(c->window.mlx);
}

static bool	map_parser(t_ctx *c, char **file)
{
	int		line;

	line = -1;
	c->window.mlx = mlx_init();
	while (file[++line])
	{
		if (file[line][0] == '\n' && c->map_size_x <= 0 && c->map_size_y <= 0)
			continue ;
		else if (is_valid_texture(nl_remove(file[line])))
			parse_texture(c, nl_remove(file[line]));
		else if (is_valid_color(nl_remove(file[line])))
			parse_color(c, nl_remove(file[line]));
		else if (is_valid_context(c) && are_texture_normalized(c))
		{
			parse_ascii_map(c, file, line);
			break ;
		}
		else
			return (false);
	}
	if (is_valid_context(c) && is_valid_ascii(c))
		return (true);
	return (false);
}

void	free_ctx(t_ctx *c)
{
	int	i;

	if (c->window.mlx)
		free(c->window.mlx);
	if (c->map_size_x > 0 || c->map_size_y > 0)
	{
		i = -1;
		while (++i < c->map_size_y)
			free(c->map[i]);
		free(c->map);
		c->map = NULL;
		c->map_size_x = -1;
		c->map_size_y = -1;
	}
	if (c->no_texture.img)
		free(c->no_texture.img);
	if (c->so_texture.img)
		free(c->so_texture.img);
	if (c->we_texture.img)
		free(c->we_texture.img);
	if (c->ea_texture.img)
		free(c->ea_texture.img);
}

int	main(int argc, char **argv)
{
	char		**file_arr;
	t_ctx		c;
	int			ret;

	ret = 0;
	init_parser(&c);
	init_ctx(&c);
	if (argc < 2)
		return (print_help(argv));
	else if (argc != 2 || !argv[1])
		return (print_err(NULL, strerror(22), 22));
	if (ft_eq(argv[1], ".cub", 2) < 1)
		return (print_err(NULL, strerror(79), 79));
	file_arr = unsplitable_file(argv[1]);
	if (file_arr && map_parser(&c, file_arr))
		graph_manager(&c);
	else
		ret = print_err(argv[1], "Isn't a parsable cub3D context.", 79);
	free_split(file_arr);
	free_ctx(&c);
	return (ret);
}
