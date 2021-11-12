/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:02:02 by conobi            #+#    #+#             */
/*   Updated: 2021/11/12 10:49:39 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	long	len;
	long	i;

	if (!s || !f)
		return (NULL);
	i = -1;
	len = ft_strlen(s);
	ret = ft_strdup(s);
	if (!ret)
		return (NULL);
	while (len > 0 && ++i <= len - 1)
		ret[i] = (*f)(i, s[i]);
	return (ret);
}
