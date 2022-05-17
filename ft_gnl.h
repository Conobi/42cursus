/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:51:21 by conobi            #+#    #+#             */
/*   Updated: 2022/05/17 14:47:01 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GNL_H
# define FT_GNL_H
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 128

/* ft_gnl_utils.c */
size_t	f_strlen(const char *s);
void	f_strjoin(char **dest, char const *src, int max);
char	*f_substr(char const *s, unsigned int start, size_t len);
char	*f_strdup(const char *s);
char	*f_strchr(const char *s, int c);

#endif
