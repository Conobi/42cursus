/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:47:54 by abastos           #+#    #+#             */
/*   Updated: 2022/10/13 19:47:26 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	debug_map(t_ctx *c)
{
	int	x;
	int	y;

	y = -1;
	while (++y < c->map_size_y)
	{
		x = -1;
		while (++x < c->map_size_x)
			printf("%d", c->map[y][x]);
		printf("\n");
	}
}

static void	graph_manager(t_ctx *c)
{
	c->window.id = mlx_new_window(c->window.mlx,
			c->window.width, c->window.height, "cub3d");
	c->img = image_handler(c);
	c->cell_size = c->no_texture.width;
	c->hitbox_max = c->cell_size / 4;
	mlx_put_image_to_window(c->window.mlx, c->window.id, c->img.img, 0, 0);
	event_listener(c);
	mlx_mouse_hide(c->window.mlx, c->window.id);
	mlx_loop(c->window.mlx);
}

static bool	map_parser(t_ctx *c, char **file)
{
	int		line;

	line = -1;
	while (file[++line])
	{
		if (file[line][0] == '\n' && c->map_size_x <= 0 && c->map_size_y <= 0)
			continue ;
		else if (is_valid_texture(nl_remove(file[line])))
			parse_texture(c, nl_remove(file[line]));
		else if (is_valid_color(nl_remove(file[line])))
			parse_color(c, nl_remove(file[line]));
		else if (is_valid_context(c))
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
	if (argc != 2 || !argv[1])
		return (print_err(NULL, strerror(22), 22));
	if (ft_eq(argv[1], ".cub", 2) < 1)
		return (print_err(NULL, strerror(79), 79));
	printf("------\nMap:\n");
	file_arr = unsplitable_file(argv[1]);
	if (file_arr && map_parser(&c, file_arr))
	{
		printf("---\nMAP OK\n");
		debug_map(&c);
		graph_manager(&c);
	}
	else
		ret = print_err(argv[1], "Isn't a parsable cub3D context.", 79);
	free_split(file_arr);
	free_ctx(&c);
	return (ret);
}
