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
# include "events.h"
# include "types.h"
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

// Engine
double		get_distance(double x1, double y1, double x2, double y2);
bool		is_air(t_ctx *c, int computed_x, int computed_y);
t_ray		create_ray(t_ctx *c, t_calc calc, double angle, int id);
void		find_wall(t_ctx *c, t_calc *calc);
t_ray		*create_rays(t_ctx *c, int fov, int rays_num);
int			generate_frame(t_ctx *c);
void		render(t_ctx *c, t_ray *rays);

// Minimap
void		draw_map(t_ctx *c, int pos_x, int pos_y);
void		draw_player(t_ctx *c, t_drawmap draw_map);
void		draw_grid(t_ctx *c, t_drawmap draw_map);
void		draw_frame(t_ctx *c, t_drawmap draw_map);

// Context functions
void		init_ctx(t_ctx *c);
void		init_parser(t_ctx *c);
void		free_ctx(t_ctx *c);

// Utils
void		draw_rect(t_ctx *c, t_rect rect);
void		draw_rect_dim(t_ctx *c, t_rectdim rect);
void		draw_line(t_ctx *c, t_line line);
void		draw_line_gradient(t_ctx *c, t_line line,
				int from_color, int to_color);
void		draw_rect_gradient(t_ctx *c, t_rect rect,
				int from_color, int to_color);
bool		out_of_bounds(t_ctx *c, int x, int y);
double		to_radians(int degrees);
bool		is_air(t_ctx *c, int computed_x, int computed_y);
int			get_facing(double angle, bool is_vertical);
int			view_distance(int color, float correction);
void		display_fps(t_ctx *c);
int			get_pixel_color_from_texture(t_img texture, int x, int y);

// Helpers
void		pixel_put(t_ctx *c, int x, int y, int color);
void		upscale(t_ctx *c);
double long	remap(double long input, double long low, double long high);

// Handlers
t_img		image_handler(t_ctx *c);
void		refresh_handler(t_ctx *c);

// Events handlers
void		event_listener(t_ctx *c);

// Move handler
void		move_player(t_ctx *c);

// Colors
int			rgba2hex(t_rgba color);
t_rgba		hex2rgba(int color);
int			linear_gradient(int from, int to, float step, bool srgb);

/*
		PARSING
						*/

/* Parser */
void		parse_color(t_ctx *c, char *str);
void		parse_texture(t_ctx *c, char *str);
void		parse_ascii_map(t_ctx *c, char **file, int line);

/* Parser utils */
int			load_fd(char *path);
int			print_err(char *line, char *err, int errno);
bool		free_split(char **str_split);
char		*nl_remove(char *str);

/* Map parser utils */
bool		free_ascii_map(t_ctx *c, bool is_err);
short		type_of_char(char c);
void		init_line(t_ctx *c, int *line);

/* File line spliter */
char		**unsplitable_file(char *filename);

/* Parser checker */
bool		is_valid_texture(char *str);
bool		is_valid_color(char *str);
bool		is_valid_context(t_ctx *c);
bool		is_valid_ascii(t_ctx *c);
bool		are_texture_normalized(t_ctx *c);

#endif
