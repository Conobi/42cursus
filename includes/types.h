/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:42:02 by abastos           #+#    #+#             */
/*   Updated: 2022/10/17 15:11:19 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_window {
	void	*mlx;
	void	*id;
	int		height;
	int		width;
	int		res;
}	t_window;

typedef struct s_ray {
	double	angle;
	double	distance;
	double	x_hit;
	double	y_hit;
	int		facing;
	int		id;
	int		cell_percent;
	bool	is_vertical;
}	t_ray;

typedef struct s_player {
	double		x;
	double		y;
	double		angle;
	int			speed;
	int			size;
	int			fov;
	char		direction;
	t_ray		*hitboxes;
}	t_player;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_ctx {
	t_window	window;
	t_player	player;
	t_img		img;
	int			rays_num;
	int			target_speed;
	int			turn_speed;
	int			cell_size;
	int			cell_map_size;
	int			map_size_x;
	int			map_size_y;
	int			f_color;
	int			c_color;
	int			fog_color;
	double		hitbox_max;
	int			**map;
	t_img		no_texture;
	t_img		so_texture;
	t_img		we_texture;
	t_img		ea_texture;
}	t_ctx;

typedef struct s_calc
{
	double	first_x;
	double	first_y;
	double	x_step;
	double	y_step;
	double	next_x;
	double	next_y;
	bool	is_wall;
	bool	is_vertical;
	int		up;
	int		right;
	int		cell_x;
	int		cell_y;
}	t_calc;

/**
 * @brief Type to create and render a rectangle in the window
 * @param x (int) The x coordinate
 * @param y (int) The y coordinate
 * @param width (int) The width of the rectangle to draw
 * @param height (int) The height of the rectangle to draw
 * @param color (int) The color of the rectangle to draw
 */
typedef struct s_rect
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
}	t_rect;

typedef struct s_rectdim
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	x_min;
	int	y_min;
	int	x_max;
	int	y_max;
	int	color;
}	t_rectdim;

typedef struct s_line {
	int	x;
	int	y;
	int	to_x;
	int	to_y;
	int	color;
}	t_line;

typedef struct s_rgba {
	short	red;
	short	green;
	short	blue;
	short	alpha;
}	t_rgba;

typedef struct s_drawmap
{
	int	width;
	int	height;
	int	weight;
	int	pos_x;
	int	pos_y;
	int	draw_x;
	int	draw_y;
}	t_drawmap;

#endif
