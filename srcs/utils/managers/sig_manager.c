/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:59:53 by abastos           #+#    #+#             */
/*   Updated: 2022/07/01 17:34:10 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is used to handle unix signals in main process
 *
 * @param sig Received signal code to handle
 */
void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_return = 256;
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
	return ;
}

/**
 * @brief This function is used to handle unix signals in heredoc
 *
 * @param sig Received signal code to handle
 */
void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
		exit(1);
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

void	fork_heredoc_sig_handler(int sig)
{
	if (sig == SIGQUIT)
		return ;
}

/**
 * @brief This function is used to handle unix signals in fork child process
 *
 * @param sig Received signal code to handle
 */
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
}
