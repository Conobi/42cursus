/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:02:02 by conobi            #+#    #+#             */
/*   Updated: 2021/11/11 19:23:12 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	size_t	len;
	size_t	i;

	if (!s || !f)
		return (NULL);
	i = -1;
	len = ft_strlen(s) - 1;
	ret = ft_strdup(s);
	if (!ret)
		return (NULL);
	while (++i <= len)
		ret[i] = (*f)(i, s[i]);
	return (ret);
}
