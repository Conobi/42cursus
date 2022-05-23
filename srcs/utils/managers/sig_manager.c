/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:59:53 by abastos           #+#    #+#             */
/*   Updated: 2022/05/23 17:56:38 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is used to handle unix signals with the provided sig code
 *
 * @param sig Signal code
 */
void	sig_handler(int sig)
{
	// printf("Received signal: %d\n", sig);
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (sig == SIGKILL)
	{
		printf("exit\n");
		exit(1);
		return ;
	}
	return ;
}

void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
		exit(1);
	if (sig == SIGKILL) //todo: not working (check for a solution to disable SIGKILL)
		return ;
}

void	fork_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		return ;
	}
	if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 10);
		return ;
	}
	if (sig == SIGKILL)
		return ;
}
