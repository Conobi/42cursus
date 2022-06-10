/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:59:53 by abastos           #+#    #+#             */
/*   Updated: 2022/06/10 09:36:01 by abastos          ###   ########lyon.fr   */
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

/**
 * @brief This function is used to handle unix signals in heredoc
 *
 * @param sig Received signal code to handle
 */
void	heredoc_sig_handler(int sig)
{
	if (sig == SIGINT)
		exit(1);
	if (sig == SIGKILL) //todo: not working (check for a solution to disable SIGKILL)
		return ;
}

/**
 * @brief This function is used to handle unix signals in fork child process
 *
 * @param sig Received signal code to handle
 */
void	fork_sig_handler(int sig)
{
	if (sig == SIGINT) //todo: return code -> 131
	{
		write(1, "\n", 1);
		return ;
	}
	if (sig == SIGQUIT) //todo: return code -> 131
	{
		write(1, "Quit: 3\n", 10);
		return ;
	}
	if (sig == SIGKILL)
		return ;
}
