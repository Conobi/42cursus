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
# include <string.h>
# include "libft.h"
# include "keys.h"
# include "mlx.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// Facing
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define SWEST 0
# define SEAST 1
# define NWEST 2
# define NEAST 3

# define RED_TXT	"\001\033[91m\002"
# define GRN_TXT	"\001\033[32m\002"
# define RESET_TXT	"\001\033[0m\002"
# define BOLD_TXT	"\001\033[1m\002"

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
	double		angle;
	int			speed;
	int			size;
	int			fov;
}	t_player;

typedef struct map {
	char	**raw;
	int		height;
	int		width;
	int		cell_size;
}	t_map;

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
	int			tick;
	int			cell_size;
	int			map_size_x;
	int			map_size_y;
	int			f_color;
	int			c_color;
	int			debug;
	t_img		no_texture;
	t_img		so_texture;
	t_img		we_texture;
	t_img		ea_texture;
	int			**map;
}	t_ctx;

typedef struct s_ray {
	double	angle;
	double	distance;
	int		facing;
	int		id;
	bool	is_vertical;
	int		cell_percent;
}	t_ray;

typedef struct s_rmap {
	int		pos_x;
	int		pos_y;
	t_ray	*rays;
}	t_rmap;

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

typedef struct s_rgba {
	short	red;
	short	green;
	short	blue;
	short	alpha;
}	t_rgba;

// Engine
t_ray		*create_rays(t_ctx *c);
int			generate_frame(t_ctx *c);
void		render(t_ctx *c, t_ray *rays);

// Minimap
void		draw_map(t_ctx *c, t_rmap rmap);

// Initialize
void		init_ctx(t_ctx *c);
void		init_parser(t_ctx *c);

// Utils
void		draw_rect(t_ctx *c, t_rect rect);
void		draw_line(t_ctx *c, t_line line);
bool		out_of_bounds(t_ctx *c, int x, int y);
double		to_radians(int degrees);
bool		is_air(t_ctx *c, int computed_x, int computed_y);
int			get_facing(double angle, bool is_vertical);
int			view_distance(int color, float correction);
void		display_fps(t_window window);
int			get_pixel_color_from_texture(t_img texture, int x, int y);

// Helpers
void		pixel_put(t_ctx *c, int x, int y, int color);
double long	remap(double long input, double long low, double long high);

// Handlers
t_img		image_handler(t_ctx *c);
void		refresh_handler(t_ctx *c);

// Events handlers
void		event_listener(t_ctx *c);

/*
		PARSING
						*/

/* Parser */
void		parse_color(t_ctx *c, char *str);
void		parse_texture(t_ctx *c, char *str);
void		parse_ascii_map(t_ctx *c, char **file, int line);

/* Parser utils */
int			load_fd(char *path);
int			print_err(int errno);
bool		free_split(char **str_split);
char		*nl_remove(char *str);

/* Map parser utils */
bool		free_ascii_map(t_ctx *c);
short		type_of_char(char c);
void		init_line(t_ctx *c, int *line);

/* File line spliter */
char		**unsplitable_file(char *filename);

/* Parser checker */
bool		is_valid_texture(char *str);
bool		is_valid_color(char *str);
bool		is_valid_context(t_ctx *c);
bool		is_valid_ascii(t_ctx *c);

#endif
