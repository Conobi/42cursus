/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:22:56 by conobi            #+#    #+#             */
/*   Updated: 2021/11/08 12:33:29 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	ret = ft_calloc((len + 1), sizeof(*ret));
	if (!ret || !s)
		return (NULL);
	if (start >= ft_strlen(s) || start >= len)
		return (ret);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}
