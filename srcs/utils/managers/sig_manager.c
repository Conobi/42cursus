/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:59:53 by abastos           #+#    #+#             */
/*   Updated: 2022/05/20 17:19:52 by abastos          ###   ########lyon.fr   */
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

static void	fork_process(int sig, siginfo_t *s_infos, void *proto)
{
	(void)s_infos;
	(void)proto;
	if (sig == SIGINT)
		return ;
}

void	fork_sig_handler(int sig) //todo: raise condition on sig with main
{
	struct sigaction	s_sig;

	(void)sig;
	s_sig.sa_sigaction = fork_process;
	s_sig.sa_flags = SA_SIGINFO; // to give signum to sigaction function
	sigaction(SIGINT, &s_sig, 0);
}
