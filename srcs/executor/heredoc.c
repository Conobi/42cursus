/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:42:02 by abastos           #+#    #+#             */
/*   Updated: 2022/09/25 18:26:57 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_heredoc(t_ctx *c, int pid, int *fd)
{
	int		status;

	(void)c;
	waitpid(pid, &status, 0);
	child_status(status);
	signal(SIGINT, fork_sig_handler);
	signal(SIGQUIT, fork_sig_handler);
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
		line = sf_add(readline(">"), &c->gbc, CMD_GB);
		if (!line)
			break ;
		if (ft_eq(line, stop, 0))
			break ;
		tmp = sf_add(ft_strjoin(line, "\n"), &c->gbc, CMD_GB);
		tmp = heredoc_env_replace(c, tmp);
		ft_putstr_fd(tmp, fd[1]);
	}
	close(fd[1]);
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

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-2);
	}
	signal(SIGINT, fork_sig_handler);
	signal(SIGQUIT, fork_heredoc_sig_handler);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		return (-2);
	}
	if (pid == 0)
	{
		signal(SIGINT, heredoc_sig_handler);
		signal(SIGQUIT, heredoc_sig_handler);
		exec_heredoc(c, fd, stop);
	}
	return (exit_heredoc(c, pid, fd));
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
				heredoc_fd = fdgb_add(create_heredoc(c, c->cmds[i].redirections[j].arg),
				&c->fdgbc, HEREDOCS_GB);
			if (heredoc_fd == -2)
				return (0);
		}
		c->cmds[i].heredoc = heredoc_fd;
	}
	return (1);
}
