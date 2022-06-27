/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:42:02 by abastos           #+#    #+#             */
/*   Updated: 2022/06/27 17:52:23 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_heredoc(int pid, int *fd)
{
	waitpid(pid, &g_return, 0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	close(fd[1]);
	if (g_return == 0)
		return (fd[0]);
	else
		return (-1);
}

static int	exec_heredoc(t_ctx *c, int *fd, const char *stop)
{
	char	*line;
	char	*tmp;

	close(fd[0]);
	while (true)
	{
		line = gb_add(readline(">"), &c->gbc, CMD_GB);
		if (!line)
			exit(256);
		if (ft_eq(line, stop, 0))
			exit(0);
		tmp = ft_strjoin(line, "\n");
		ft_putstr_fd(tmp, fd[1]);
		free(tmp);
	}
	exit(0);
}

/**
 * @brief This function create an heredoc instance
 *
 * @param c Minishell context struct
 * @param stop EOF for termination of heredoc
 */
int	create_heredoc(t_ctx *c, const char *stop)
{
	pid_t	pid;
	int		fd[2];

	(void)c;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	signal(SIGINT, heredoc_sig_handler);
	signal(SIGQUIT, heredoc_sig_handler);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		exec_heredoc(c, fd, stop);
	else
		return (exit_heredoc(pid, fd));
	return (1);
}
