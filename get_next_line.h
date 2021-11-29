/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:51:21 by conobi            #+#    #+#             */
/*   Updated: 2021/11/19 18:52:17 by conobi           ###   ########lyon.fr   */
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
void	*f_memcpy(void *dst, const void *src, size_t n);
char	*f_strjoin(char const *s1, char const *s2);
char	*f_substr(char const *s, unsigned int start, size_t len);
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
