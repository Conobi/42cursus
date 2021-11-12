/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:49:48 by conobi            #+#    #+#             */
/*   Updated: 2021/11/12 15:53:42 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	len;
	size_t	start;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) - 1;
	start = 0;
	while (ft_strchr(set, s1[start]))
		start++;
	while (ft_strchr(set, s1[len]) && len > start)
		len--;
	ret = ft_substr(s1, start, len - start + 1);
	return (ret);
}
