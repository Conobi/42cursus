/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:50:13 by conobi            #+#    #+#             */
/*   Updated: 2021/11/02 17:16:47 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	i;

	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	i = -1;
	while (src[++i] && dstsize > dst_size && i < dstsize - dst_size - 1)
		dst[dst_size + i] = src[i];
	dst[dst_size + i] = '\0';
	if (dstsize >= dst_size)
		return (dst_size + src_size);
	else
		return (src_size + dstsize);
}
