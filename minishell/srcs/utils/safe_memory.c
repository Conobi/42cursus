/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:58:32 by conobi            #+#    #+#             */
/*   Updated: 2022/08/12 15:08:01 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function display an error and exit the program with ENOMEM code
 *
 * @param garbcl Pointer to garbage collector
 */
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

/**
 * @brief This function is identical to gb_add function
 * but throw error if allocation fails.
 *
 * @param ptr Pointer to the allocated memory
 * @param garbcl Pointer to garbage collector
 * @param type Type of the value added to the garbage collector
 * @return void* Returns pointer to the allocated memory
 */
void	*sf_add(void *ptr, t_garbc **garbcl, const short type)
{
	void	*ret;

	ret = gb_add(ptr, garbcl, type);
	if (ptr != NULL && ret == NULL)
		enomem_error(garbcl);
	return (ret);
}

/**
 * @brief This function is identical to gb_calloc function
 * but throw error if allocation fails.
 *
 * @param count Number of bytes to allocate
 * @param size Size of the allocated memory
 * @param type Type of the value added to the garbage collector
 * @param last Pointer to last node in garbage collector
 * @return void* Returns pointer to the allocated memory
 */
void	*sf_calloc(size_t count, size_t size, const short type, t_garbc **last)
{
	void	*ret;

	ret = gb_calloc(count, size, type, last);
	if (ret == NULL)
		enomem_error(last);
	return (ret);
}
