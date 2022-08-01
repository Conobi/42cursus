/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:42:02 by abastos           #+#    #+#             */
/*   Updated: 2022/08/01 18:22:24 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_heredoc(int pid, int *fd)
{
	int		status;

	waitpid(pid, &status, 0);
	child_status(status);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	close(fd[1]);
	if (g_return == 0)
		return (fd[0]);
	else
		return (-2);
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
			exit(0);
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
	signal(SIGINT, fork_sig_handler);
	signal(SIGQUIT, fork_heredoc_sig_handler);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-2);
	}
	if (pid == 0)
	{
		signal(SIGINT, heredoc_sig_handler);
		signal(SIGQUIT, heredoc_sig_handler);
		exec_heredoc(c, fd, stop);
	}
	return (exit_heredoc(pid, fd));
}

int	open_heredocs(t_ctx *c)
{
	int	i;
	int	j;
	int	heredoc_fd;

	i = -1;
	heredoc_fd = 0;
	while (++i < c->ncmds)
	{
		j = -1;
		while (++j < c->cmds[i].redc)
		{
			if (c->cmds[i].redirections[j].type == HRDC_TK)
				heredoc_fd = create_heredoc(c, c->cmds[i].redirections[j].arg);
			if (heredoc_fd == -2)
				return (0);
		}
		c->cmds[i].heredoc = heredoc_fd;
	}
	// if (c->heredoc_errored)
	// {
	// 	syntax_err(c, c->heredoc_errored);
	// 	c->heredoc_errored = NULL;
	// 	return (0);
	// }
	return (1);
}
