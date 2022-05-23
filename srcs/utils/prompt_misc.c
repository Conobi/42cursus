/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_misc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:05:37 by abastos           #+#    #+#             */
/*   Updated: 2022/05/23 16:24:48 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * todo: implement a function to execute a command like curl or ls
*/

/**
 * @brief This function is used to get the current weather
 * emoji and display it in the prompt (bcs why not !)
 *
 * @param c Minishell context struct
 */
void	get_weather(t_ctx *c)
{
	int		link[2];
	pid_t	pid;
	char	*args[5];

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
		args[0] = "curl";
		args[1] = "-s";
		args[2] = "https://kiyo.ooo/f/meteoshell.php";
		args[3] = "-k";
		args[4] = 0;
		exit(execve(find_exec(c, "curl"), args, c->env_list));
	}
	else
	{
		close(link[1]);
		read(link[0], c->weather_emoji, 4);
		close(link[0]);
		waitpid(pid, &c->return_code, 0);
	}
}

/**
 * @brief This function get the current git branch if available
 *
 * @param c Minishell context struct
 * @return char* Returns branch name (value in garbage collector)
 */
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
