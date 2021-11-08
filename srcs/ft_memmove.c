/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:39:46 by conobi            #+#    #+#             */
/*   Utdstated: 2021/11/07 17:42:42 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tdst;
	unsigned char	*tsrc;

	if (!dst && !src)
		return (NULL);
	tdst = (unsigned char *)dst;
	tsrc = (unsigned char *)src;
	if (tsrc < tdst)
	{
		tdst += len;
		tsrc += len;
		while (len--)
			*--tdst = *--tsrc;
	}
	else
		while (len--)
			*tdst++ = *tsrc++;
	return (dst);
}
