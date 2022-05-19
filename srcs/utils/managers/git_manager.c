/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:05:37 by abastos           #+#    #+#             */
/*   Updated: 2022/05/19 20:24:50 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_weather(t_ctx *c)
{
	int		link[2];
	char	*args[2];
	pid_t	pid;

	if (pipe(link) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		dup2 (link[1], STDOUT_FILENO);
		close(link[0]);
		close(link[1]);
		args[0] = "https://kiyo.ooo/f/meteoshell.php";
		args[1] = "-k";
		printf("%s\n", find_exec(c, "curl"));
		exit(execve(find_exec(c, "curl"), args, c->env_list));
	}
	else
	{
		close(link[1]);
		printf("%c\n", link[0]);
		c->weather_emoji = link[0];
		waitpid(pid, &c->return_code, 0);
	}
}

char	*get_branch(t_ctx *c)
{
	int		fd;
	char	*branch;
	char	*new_branch;

	fd = open(".git/HEAD", O_RDWR);
	if (fd < 0)
		return (NULL);
	branch = gb_add(ft_gnl(fd),
			&c->gbc, CMD_GB);
	new_branch = gb_add(ft_substr(branch, 16, ft_strlen(branch) - 17),
			&c->gbc, CMD_GB);
	close(fd);
	return (new_branch);
}
