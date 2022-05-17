/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:59:50 by abastos           #+#    #+#             */
/*   Updated: 2022/05/18 00:26:18 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_table(t_table *table, char **args)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	table->commands_num = 1;
	table->command_table = malloc(sizeof(t_command) * table->commands_num);
	table->process = malloc(sizeof(pid_t) * table->commands_num);
	table->command_table[0] = *new;
	table->command_table[0].args = args;
	table->command_table[0].piped = false;
	table->command_table[0].outfiles = ft_split(">", '>');
	// table->command_table[1] = *new;
	// table->command_table[1].args = ft_split("head -n 5", ' ');
	// table->command_table[1].piped = true;
	// table->command_table[1].outfiles = ft_split(">", '>');
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

/**
 * @brief This function is used to handle unix signals with the provided sig code
 *
 * @param sig Signal code
 */
void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (sig == SIGQUIT)
	{
		printf("exit\n");
		exit(SIGQUIT);
		return ;
	}
	return ;
}

/**
 * @brief This function is used to create shell promp with custom path
 *
 * @param c Minishell context struct
 * @param path New path to display in prompt
 */
void	gen_prompt(t_ctx *c, const char *path, const char *branch)
{
	if (branch)
	{
		c->prompt = ft_aconcat(24, WHT_FG, "",
				WHT_BG, BLK_FG, BOLD, "  ", WHT_FG, RED_BG,
				" ", "Minishell ", path, " ",
				RED_FG, BLU_BG, " ", WHT_FG,
				"⚡️git:(", branch, ") ", RESET, BLU_FG, " ", RESET, WHT_FG);
		return ;
	}
	c->prompt = ft_aconcat(15, WHT_FG, "",
				WHT_BG, BLK_FG, BOLD, "  ", WHT_FG, RED_BG,
				" ", "Minishell ", path, RESET,
					RED_FG, " ", RESET, WHT_FG);
}

static void	ctx_init(t_ctx *c, t_table *table)
{
	c->gbc = gb_init();
	if (!c->gbc)
		exit_shell(table, c, 1);
	gen_prompt(c, format_path(c), get_branch(c));
	c->last_path = get_path(c);
	c->history_fd = open("./.minishell_history",
			O_CREAT | O_RDWR, 0000644);
	c->last_entry = NULL;
	c->parser.squoted = -1;
	c->parser.dquoted = -1;
}

int	main(int argc, char **argv, char **env)
{
	t_ctx			c;
	t_table			*table;

	(void)argc;
	(void)argv;
	(void)env;
	signal(SIGINT, sig_handler);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	ctx_init(&c, table);
	init_history(&c);
	create_env(&c, env);
	while (true)
	{
		c.entry = gb_add(readline(c.prompt), &c.gbc, CMD_GB);
		if (c.entry)
		{
			if (ft_strlen(c.entry) == 0)
			{
				rl_on_new_line();
				rl_redisplay();
			}
			else
			{
				history(&c);
				if (ft_strncmp(c.entry, "exit", ft_strlen(c.entry)) == 0)
				{
					printf("exit SHELL\n");
					exit_shell(table, &c, 0);
				}
				else if (ft_strncmp(c.entry, "cd", 2) == 0)
					b_cd(&c, c.entry);
				else if (ft_strncmp(c.entry, "pwd", 3) == 0)
					b_pwd(&c);
				// else if (ft_strncmp(c.entry, "echo", 4) == 0)
				// 	b_echo(c.entry);
				else
				{
					create_table(table, gb_add(ft_split(c.entry, ' '),
							&c.gbc, CMD_GB));
					exec(&c, table);
				}
			}
			gb_delete(&c.gbc, CMD_GB);
		}
		else
			sig_handler(SIGQUIT);
	}
}
