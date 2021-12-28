/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:29:28 by conobi            #+#    #+#             */
/*   Updated: 2021/12/13 15:12:22 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	ret = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(*ret));
	if (!ret)
		return (NULL);
	while (s1[++j])
		ret[++i] = s1[j];
	j = -1;
	while (s2[++j])
		ret[++i] = s2[j];
	ret[++i] = 0;
	return (ret);
}
