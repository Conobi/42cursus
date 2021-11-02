/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:03:50 by conobi            #+#    #+#             */
/*   Updated: 2021/11/02 18:05:19 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int		len;
	int		i;
	char	*ptr;

	len = -1;
	i = -1;
	while (src[++len])
		;
	ptr = malloc(sizeof(ptr) * (len + 1));
	if (ptr == 0)
		return (NULL);
	while (src[++i])
		ptr[i] = src[i];
	ptr[i] = '\0';
	return (ptr);
}
