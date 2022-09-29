/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:48:12 by conobi            #+#    #+#             */
/*   Updated: 2022/09/29 02:14:14 by conobi           ###   ########lyon.fr   */
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
	int		debug;
}	t_parser;

/* Parser utils */
char	*load_file(char *path);
int		print_err(int errno);

/* Parser checker */
bool	is_valid_texture(char *str);
bool	is_valid_color(char *str);
bool	is_valid_context(t_parser *parser_ctx);
bool	is_valid_ascii(t_parser *parser_ctx);

char	**char_split(char *str, char *charset);

#endif
