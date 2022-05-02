/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:59:50 by abastos           #+#    #+#             */
/*   Updated: 2022/03/30 16:52:45 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_table(t_table *table, char **args)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	table->commands_num = 2;
	table->command_table = malloc(sizeof(t_command) * table->commands_num);
	table->process = malloc(sizeof(pid_t) * table->commands_num);
	table->command_table[0] = *new;
	table->command_table[0].args = args;
	table->command_table[0].piped = true;
	table->command_table[0].outfiles = ft_split(">", '>');
	table->command_table[1] = *new;
	table->command_table[1].args = ft_split("head -n 5", ' ');
	table->command_table[1].piped = true;
	table->command_table[1].outfiles = ft_split(">", '>');
	// table->command_table[2] = *new;
	// table->command_table[2].args = ft_split("cut -c 3-5", ' ');
	// table->command_table[2].piped = true;
	// table->command_table[2].outfiles = ft_split(">", '>');
	// table->command_table[3] = *new;
	// table->command_table[3].args = ft_split("echo a b c d", ' ');
	// table->command_table[3].piped = false;
	// table->command_table[3].outfiles = ft_split(">", '>');
	// table->command_table[4] = *new;
	// table->command_table[4].args = ft_split("echo a b c d", ' ');
	// table->command_table[4].piped = false;
	// table->command_table[4].outfiles = ft_split(">", '>');
}

void	signal_handler(int sig)
{
	(void) sig;
	return ;
}

int	main(int argc, char **argv, char **env)
{
	char	*entry;
	t_table	*table;

	(void)argc;
	(void)argv;
	(void)env;
	table = malloc(sizeof(t_table));
	signal(SIGINT, signal_handler);
	if (!table)
		return (1);
	while (true)
	{
		entry = readline(ft_strjoin(ft_strjoin(RED, "minishell "), RESET));
		if (ft_strncmp(entry, "exit", 5) == 0)
			exit_shell(table);
		add_history(entry);
		create_table(table, ft_split(entry, ' '));
		exec(table);
	}
}
