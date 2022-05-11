/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:59:50 by abastos           #+#    #+#             */
/*   Updated: 2022/05/11 18:50:16 by conobi           ###   ########lyon.fr   */
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

static void ctx_init(t_ctx *c)
{
	c->gbc = gb_init();
	if (!c->gbc)
		exit_shell(c, 1);
	c->prompt = gb_add(ft_aconcat(15, WHT_FG, "", WHT_BG, BLK_FG,
					BOLD, "  ", WHT_FG, RED_BG,
					" ", "Minishell $_ ", RESET,
					RED_FG, " ", RESET, WHT_FG), &(c->gbc), PERM_GB);
	c->parser.squoted = -1;
	c->parser.dquoted = -1;
}

int	main(int argc, char **argv, char **env)
{
	t_ctx	c;

	(void)argc;
	(void)argv;
	(void)env;
	ctx_init(&c);
	signal(SIGINT, signal_handler);
	while (true)
	{
		c.entry = gb_add(readline(c.prompt), &c.gbc, ENTRY_GB);
		parser(&c);
		add_history(c.entry);
		// create_table(table, ft_split(entry, ' '));
		// exec(table);
	}
}
