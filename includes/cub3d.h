/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:22:39 by abastos           #+#    #+#             */
/*   Updated: 2022/08/16 05:32:36 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>
# include <stdbool.h>
# include <math.h>
# include "libft.h"
# include "../mlx/mlx.h"

# define WIN_W 1600
# define WIN_H 1200
# define RESOLUTION 1
# define CELL_SIZE 20
# define PLAYER_SIZE 8
# define FOV 60

# define PLAYER_SPEED 2
# define TICK 60
# define SCALE 2

// Facing
# define WEST 1
# define EAST 2
# define NORTH 3
# define SOUTH 4

// Keybindings
# define MVUP_KEY 13
# define DVDW_KEY 1
# define MVR_KEY 0
# define MVL_KEY 2
# define EXIT_KEY 53

typedef struct s_window {
	void	*mlx;
	void	*id;
	int		height;
	int		width;
	int		res;
}	t_window;

typedef struct s_player {
	double		x;
	double		y;
	int			speed;
	double		angle;
}	t_player;

typedef struct map {
	char	**raw;
	int		height;
	int		width;
}	t_map;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_ctx {
	t_window	window;
	t_player	player;
	t_map		map;
	t_img		img;
}	t_ctx;

typedef struct s_rmap {
	int		pos_x;
	int		pos_y;
	int		scale;
	t_list	*rays;
}	t_rmap;

// todo: create a chained list of all rays
typedef struct s_ray {
	double	angle;
	double	distance;
	bool	vertical;
	int		facing;
}	t_ray;

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

typedef struct s_line {
	int	x;
	int	y;
	int	to_x;
	int	to_y;
	int	color;
}	t_line;

// Engine
t_list		*create_rays(t_ctx *c);
int			generate_frame(t_ctx *c);

// Minimap
void		draw_map(t_ctx *c, t_rmap rmap);

// Initialize
void		init_ctx(t_ctx *c);

// Utils
int			draw_rect(t_ctx *c, t_rect rect);
int			draw_line(t_ctx *c, t_line line);
bool		out_of_bounds(t_ctx *c, double x, double y);
double		to_radians(int degrees);

// Helpers
void		pixel_put(t_ctx *c, int x, int y, int color);
double long	remap(double long input, double long low, double long high);

// Handlers
t_img		image_handler(t_ctx *c);
void		refresh_handler(t_ctx *c);

// Events handlers
void		event_listener(t_ctx *c);

#endif
