/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:50:09 by conobi            #+#    #+#             */
/*   Updated: 2022/01/21 18:05:53 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_help(char **argv)
{
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(22), 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd("\e[92m\e[1mUSAGE:\e[0m ", 1);
	ft_putstr_fd(argv[0], 1);
	ft_putstr_fd(" \e[96m\e[4minfile cmd1 cmd2 outfile\e[0m\n", 1);
}

int	open_files(char *infile, char *outfile, t_data *data)
{
	data->in_fd = open(infile, O_RDONLY);
	if (data->in_fd == -1)
		perr_print(infile);
	data->out_fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->out_fd == -1)
		perr_print(outfile);
	if (data->in_fd || data->out_fd == -1)
		return (1);
	return (0);
}

void	close_files(char *infile, char *outfile, t_data *data)
{
	int	st;

	if (data->in_fd != -1)
	{
		st = close(data->in_fd);
		if (st == -1)
			perr_print(infile);
	}
	if (data->out_fd != -1)
	{
		st = close(data->out_fd);
		if (st == -1)
			perr_print(outfile);
	}
}

void	child_manager(t_data *data, char **cmd, short type)
{
	if (!type)
	{
		perr_cb("dup2", dup2(data->in_fd, STDIN_FILENO), -1);
		perr_cb("dup2", dup2(data->piped[1], STDOUT_FILENO), -1);
	}
	else if (type == 1)
	{
		perr_cb("dup2", dup2(data->piped[0], STDIN_FILENO), -1);
		perr_cb("dup2", dup2(data->out_fd, STDOUT_FILENO), -1);
	}
	else if (type == 2)
	{
		perr_cb("dup2", dup2(data->in_fd, STDIN_FILENO), -1);
		perr_cb("dup2", dup2(data->out_fd, STDOUT_FILENO), -1);
	}
	// int	i;
	// i = -1;
	// while (data->env[++i])
	// {
	// 	ft_putstr_fd(data->env[i], 2);
	// 	ft_putstr_fd("\n", 2);
	// }
	perr_cb("close", close(data->piped[0]), -1);
	perr_cb("close", close(data->piped[1]), -1);
	if (cmd[0])
	{
		perr_cb(cmd[0],
			execve(cmd[0], cmd, data->env), -1);
	}
}

void	single_manager(t_data *data, char **argv)
{
	pid_t	pid;
	char	**cmd;

	if (data->cmd1_args[0])
		cmd = data->cmd1_args;
	else
		cmd = data->cmd2_args;
	// printf("Single manager (%s)\n", cmd[0]);
	pid = fork();
	if (pid == -1)
		perr_print("fork");
	if (pid == 0)
		child_manager(data, cmd, 2);
	else
		close_files(argv[1], argv[4], data);
}

void	double_manager(t_data *data, char **argv)
{
	pid_t	pid;

	// printf("Double manager\n");
	pid = fork();
	if (pid == -1)
		perr_print("fork");
	if (pid == 0)
		child_manager(data, data->cmd1_args, 0);
	else
	{
		pid = fork();
		if (pid == -1)
			perr_print("fork");
		if (pid == 0)
			child_manager(data, data->cmd2_args, 1);
	}
	if (pid != 0)
		close_files(argv[1], argv[4], data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc == 5)
	{
		data.env = env;
		data.status = pipe(data.piped);
		if (data.status != 0)
			return (perr_print("pipe"));
		open_files(argv[1], argv[4], &data);
		slice_binary_args(argv[2], argv[3], &data);
		double_manager(&data, argv);
		// else if (!data.cmd1_args[0] && data.cmd2_args[0])
		// 	single_manager(&data, argv);
		// else
		// 	close_files(argv[1], argv[4], &data);
		return (0);
	}
	else
		print_help(argv);
	return (1);
}
