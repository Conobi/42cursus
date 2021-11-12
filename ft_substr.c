/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:22:56 by conobi            #+#    #+#             */
/*   Updated: 2021/11/12 15:02:17 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	strlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (len <= strlen)
		ret = ft_calloc((len + 1), sizeof(char));
	else
		ret = ft_calloc((strlen + 1), sizeof(char));
	if (!ret)
		return (NULL);
	if (start > strlen)
		return (ret);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}
