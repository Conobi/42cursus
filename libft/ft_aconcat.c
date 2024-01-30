/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aconcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:14:08 by abastos           #+#    #+#             */
/*   Updated: 2022/04/26 19:09:02 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*concatenate(va_list ap, int argc, size_t len)
{
	char	*curr;
	char	*rtn;
	int		i;
	int		j;
	int		k;

	rtn = ft_calloc(len + 1, sizeof(char));
	if (!rtn)
		return (NULL);
	i = 0;
	j = 0;
	while (i < argc)
	{
		curr = va_arg(ap, char *);
		k = 0;
		while (curr && curr[k] != '\0')
			rtn[j++] = curr[k++];
		i++;
	}
	rtn[j] = '\0';
	va_end(ap);
	return (rtn);
}

char	*ft_aconcat(int argc, ...)
{
	int		i;
	va_list	args;
	va_list	args_len;
	char	*curr;
	size_t	len;

	va_start(args, argc);
	va_copy(args_len, args);
	i = 0;
	len = 0;
	while (i < argc)
	{
		curr = va_arg(args_len, char *);
		if (curr)
			len += ft_strlen(curr);
		i++;
	}
	va_end(args_len);
	return (concatenate(args, argc, len));
}
