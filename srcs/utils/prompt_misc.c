/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_misc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:05:37 by abastos           #+#    #+#             */
/*   Updated: 2022/07/01 16:00:34 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gen_sad_prompt(t_ctx *c, const char *path)
{
	free(c->prompt);
	c->prompt = ft_aconcat(4, "Minishell ", path, " ", "> ");
}

/**
 * @brief This function is used to create shell promp with custom path
 *
 * @param c Minishell context struct
 * @param path New path to display in prompt
 * @param branch Git branch to display in prompt
 */
void	gen_prompt(t_ctx *c, const char *path, const char *branch)
{
	char	*status;

	free(c->prompt);
	if (g_return == 0)
		status = "✓";
	else
		status = gb_add(ft_strjoin("✖ ",
					gb_add(ft_itoa(g_return),
						&c->gbc, CMD_GB)), &c->gbc, CMD_GB);
	if (branch)
	{
		c->prompt = ft_aconcat(28, WHT_FG, "",
				WHT_BG, BLK_FG, BOLD, " ",
				c->weather_emoji, "  ", WHT_FG, ACC_BG,
				" ", "Minishell ", "  ", path, " ", status, " ",
				ACC_FG, BLU_BG, " ", WHT_FG,
				" ", branch, " ", RESET, BLU_FG, " ", RESET);
		return ;
	}
	c->prompt = ft_aconcat(21, WHT_FG, "",
			WHT_BG, BLK_FG, BOLD, " ", c->weather_emoji, "  ", WHT_FG, ACC_BG,
			" ", "Minishell ", "  ", path, " ", status, " ", RESET,
			ACC_FG, " ", RESET);
}

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
		exit(execve(find_exec(c, "curl"),
				(char *[5]){"curl", "-s",
				"https://kiyo.ooo/f/meteoshell.php", "-k", 0}, convert_env(c))); // todo: fix if path is unset
	}
	else
	{
		close(link[1]);
		read(link[0], c->weather_emoji, 4);
		close(link[0]);
		waitpid(pid, &g_return, 0);
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
