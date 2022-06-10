/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:42:02 by abastos           #+#    #+#             */
/*   Updated: 2022/06/10 09:23:47 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function create an heredoc instance
 *
 * @param c Minishell context struct
 */
int	create_heredoc(t_ctx *c, char *stop)
{
	pid_t	pid;
	int		fd[2];
	char	*line;
	char	*tmp;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, heredoc_sig_handler);
		signal(SIGQUIT, heredoc_sig_handler);
		close(fd[0]);
		while (true)
		{
			line = readline(">");
			if (ft_eq(line, stop, 0))
				exit(0);
			tmp = ft_strjoin(line, "\n");
			ft_putstr_fd(tmp, fd[1]);
			free(tmp);
		}
		exit(0);
	}
	else
	{
		waitpid(pid, &c->return_code, 0);
		close(fd[1]);
		if (c->return_code == 0)
			return (fd[0]);
	}
	return (1);
}
