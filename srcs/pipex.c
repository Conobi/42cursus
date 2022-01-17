/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:50:09 by conobi            #+#    #+#             */
/*   Updated: 2022/01/17 19:56:31 by conobi           ###   ########lyon.fr   */
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

int	main(int argc, char *argv[], char **env)
{
	t_data	data;
	// pid_t	pid;
	// int		status;

	if (argc == 5)
	{
		open_files(argv[1], argv[4], &data);
		data.cmd1_path = find_binary_path(argv[2], env);
		if (!data.cmd1_path)
			perr_print(argv[2]);
		data.cmd2_path = find_binary_path(argv[3], env);
		if (!data.cmd1_path)
			perr_print(argv[3]);
		close_files(argv[1], argv[4], &data);
		return (0);
	}
	else
		print_help(argv);
	return (1);
}
