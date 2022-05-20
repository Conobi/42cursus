/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:42:02 by abastos           #+#    #+#             */
/*   Updated: 2022/05/20 17:01:56 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_heredoc(t_ctx *c)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	(void)c;
	if (pipe(fd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		signal(SIGINT, fork_sig_handler);
		close(fd[0]);
		while (true)
		{
			line = readline(">");
			if (ft_eq(line, "exit", 0)) //todo: edit with EOF arg
				exit(0);
			ft_putstr_fd(ft_strjoin(line, "\n"), fd[1]);
		}
		exit(0);
	}
	else
	{
		waitpid(pid, &c->return_code, 0);
		close(fd[1]);
		if (c->return_code == 0)
		{
			while (true)
			{
				line = gb_add(ft_gnl(fd[0]), &c->gbc, CMD_GB);
				if (!line)
					break ;
				printf("%s", line);
			}
		}
	}
}
