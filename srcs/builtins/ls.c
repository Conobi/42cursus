/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:50:42 by abastos           #+#    #+#             */
/*   Updated: 2022/06/13 19:35:42 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function is used to print ls output with color syntax
 * for directories & files
 *
 * @param c Minishell context struct
 * @param dir Dir struct returned by opendir() function
 * @param filename Current filename to print
 */
static void	print_ls(t_ctx *c, DIR *dir, char *filename)
{
	if (dir)
	{
		printf("%s     ", (char *)gb_add(
				ft_aconcat(5, BLU_FG, " ", filename, "/", RESET),
				&c->gbc, CMD_GB));
		closedir(dir);
		return ;
	}
	if (ft_eq(filename, ".c", 2))
	{
		printf("%s     ", (char *)gb_add(
				ft_aconcat(4, WHT_FG, " ", filename, RESET),
				&c->gbc, CMD_GB));
		return ;
	}
	if (ft_eq(filename, ".cpp", 2))
	{
		printf("%s     ", (char *)gb_add(
				ft_aconcat(4, WHT_FG, " ", filename, RESET),
				&c->gbc, CMD_GB));
		return ;
	}
	printf("%s     ", (char *)gb_add(
			ft_aconcat(3, WHT_FG, filename, RESET),
			&c->gbc, CMD_GB));
}

/**
 * @brief This function is used to select if a file is a folder or a regular file
 *
 * @param c Minishell context struct
 * @param fd Out pipe (contains ls output)
 */
static void	dir_or_file(t_ctx *c, int fd)
{
	char		*file;
	char		*new_file;
	DIR			*dir;

	while (true)
	{
		file = gb_add(ft_gnl(fd), &c->gbc, CMD_GB);
		if (!file)
			break ;
		new_file = gb_add(ft_substr(file, 0, ft_strlen(file) - 1),
				&c->gbc, CMD_GB);
		dir = opendir(gb_add(ft_aconcat(4, get_path(c), "/", new_file, "/"),
					&c->gbc, CMD_GB));
		print_ls(c, dir, new_file);
	}
	printf("\n");
}

/**
 * @brief this function is an ls but better (no args)
 *
 * @param c Minishell context struct
 * @param table Commands table struct
 * @param cmd Index of the command to execute
 */
void	b_ls(t_ctx *c, t_table *table, int cmd)
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
		//todo: remove this
		exit(execve(table->command_table[cmd].exec_path,
				table->command_table[cmd].args, NULL));
	}
	else
	{
		waitpid(pid, &c->return_code, 0);
		close(link[1]);
		dir_or_file(c, link[0]);
		close(link[0]);
	}
}
