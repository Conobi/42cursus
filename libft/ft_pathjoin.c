/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:55:14 by conobi            #+#    #+#             */
/*   Updated: 2022/01/17 18:55:27 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_pathjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	ret = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 2), sizeof(*ret));
	if (!ret)
		return (NULL);
	while (s1[++j])
		ret[++i] = s1[j];
	j = -1;
	ret[++i] = '/';
	while (s2[++j])
		ret[++i] = s2[j];
	ret[++i] = 0;
	return (ret);
}
