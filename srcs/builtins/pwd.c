/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:23:28 by abastos           #+#    #+#             */
/*   Updated: 2022/05/12 00:47:58 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is a clone of pwd command for builtins
 *
 */
void	b_pwd(void)
{
	char	pwd[256];

	printf("%s\n", getcwd(pwd, sizeof(pwd)));
}
