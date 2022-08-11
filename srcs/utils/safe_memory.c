/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:58:32 by conobi            #+#    #+#             */
/*   Updated: 2022/08/11 19:07:13 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	enomem_error(t_garbc **garbcl)
{
	ft_putstr_fd(RED_FG, 2);
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(ENOMEM), 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(RESET, 2);
	gb_clear(garbcl);
	exit(ENOMEM);
}

void	*sf_add(void *ptr, t_garbc **garbcl, const short type)
{
	void	*ret;

	ret = gb_add(ptr, garbcl, type);
	if (ptr != NULL && ret == NULL)
		enomem_error(garbcl);
	return (ret);
}

void	*sf_calloc(size_t count, size_t size, const short type, t_garbc **last)
{
	void	*ret;

	ret = gb_calloc(count, size, type, last);
	if (ret == NULL)
		enomem_error(last);
	return (ret);
}
