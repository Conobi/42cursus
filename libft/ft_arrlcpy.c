/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:29:09 by conobi            #+#    #+#             */
/*   Updated: 2021/12/30 20:05:07 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arrlcpy(int *dst, const int *src, size_t dstsize)
{
	size_t	i;

	i = -1;
	while (++i < dstsize)
		dst[i] = src[i];
	return (dstsize);
}
