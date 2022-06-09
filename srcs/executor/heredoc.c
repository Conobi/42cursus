/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:42:02 by abastos           #+#    #+#             */
/*   Updated: 2022/06/09 19:57:34 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function create an heredoc instance
 *
 * @param c Minishell context struct
 */
void	create_heredoc(t_ctx *c, char *stop)
{
	pid_t	pid;
	int		fd[2];
	char	*line;
	char	*tmp;

	if (pipe(fd) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
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
		{
			while (true)
			{
				line = ft_gnl(fd[0]);
				if (!line)
					break ;
				printf("%s", line);
				free(line);
			}
		}
	}
}
