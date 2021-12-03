/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:51:21 by conobi            #+#    #+#             */
/*   Updated: 2021/12/03 20:17:24 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

/* get_next_line.c */
char	*get_next_line(int fd);

/* get_next_line_utils.c */
size_t	f_strlen(const char *s);
void	f_strjoin(char **dest, char const *src, int max);
char	*f_substr(char const *s, unsigned int start, size_t len);
char	*f_strdup(const char *s);
char	*f_strchr(const char *s, int c);

// char	*f_substr(char const *s, unsigned int start, size_t len);

/** FOR TESTING PURPOSES :
 * gcc -Werror -Wall -Wextra get_next_line.c get_next_line_utils.c \
 * test.c -D BUFFER_SIZE=42 -o exec && ./exec
 */

// typedef struct s_read
// {
// 	int		nbytes;
// 	char	*buf;
// }	t_read;

#endif
