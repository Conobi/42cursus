/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:48:12 by conobi            #+#    #+#             */
/*   Updated: 2022/10/03 15:53:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>
# include <stdbool.h>
# include <math.h>
# include <string.h>
# include "libft.h"

typedef struct s_parser
{
	bool	file_err;
	int		map_size_x;
	int		map_size_y;
	int		f_color;
	int		c_color;
	int		debug;
	void	*no_texture;
	void	*so_texture;
	void	*we_texture;
	void	*ea_texture;
}	t_parser;

# define RED_TXT	"\001\033[91m\002"
# define GRN_TXT	"\001\033[32m\002"
# define RESET_TXT	"\001\033[0m\002"
# define BOLD_TXT	"\001\033[1m\002"

/* Parser */
void	parse_color(t_parser *parser_ctx, char *str);

/* Parser utils */
char	*load_file(char *path);
int		print_err(int errno);
int		rgba2hex(int r, int g, int b, int a);

/* Parser checker */
bool	is_valid_texture(char *str);
bool	is_valid_color(char *str);
bool	is_valid_context(t_parser *parser_ctx);
bool	is_valid_ascii(t_parser *parser_ctx);

char	**char_split(char *str, char *charset);

#endif
