/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:23:28 by abastos           #+#    #+#             */
/*   Updated: 2022/05/12 19:16:16 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is a clone of pwd command for builtins
 *
 */
void	b_pwd(void)
{
	printf("%s\n", getcwd(NULL, sizeof(char) * 126));
}
