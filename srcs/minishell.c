/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:59:50 by abastos           #+#    #+#             */
/*   Updated: 2022/05/23 17:33:07 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_table(t_ctx *c, t_table *table, char **args)
{
	t_command	*new;

	new = gb_calloc(sizeof(t_command), 1, CMD_GB, &c->gbc);
	table->commands_num = 1;
	table->command_table = gb_calloc(sizeof(t_command), table->commands_num, CMD_GB, &c->gbc);
	table->process = gb_calloc(sizeof(pid_t), table->commands_num, CMD_GB, &c->gbc);
	table->command_table[0] = *new;
	table->command_table[0].args = args;
	table->command_table[0].piped = false;
	table->command_table[0].outfiles = gb_split(c, ">", '>');
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
 * @brief This function is used to create shell promp with custom path
 *
 * @param c Minishell context struct
 * @param path New path to display in prompt
 */
void	gen_prompt(t_ctx *c, const char *path, const char *branch)
{
	char	*status;

	free(c->prompt);
	// printf("%d -> %d\n", c->return_code, WEXITSTATUS(c->return_code)); // debug
	if (WEXITSTATUS(c->return_code) == 0)
		status = "✓";
	else
		status = gb_add(ft_strjoin("✖ ",
					gb_add(ft_itoa(WEXITSTATUS(c->return_code)),
						&c->gbc, CMD_GB)), &c->gbc, CMD_GB);
	if (branch)
	{
		c->prompt = ft_aconcat(27, WHT_FG, "",
				WHT_BG, BLK_FG, BOLD, "  ",
				c->weather_emoji, "  ", WHT_FG, RED_BG,
				" ", "Minishell ", path, " ", status, " ",
				RED_FG, BLU_BG, " ", WHT_FG,
				"⚡️git:(", branch, ") ", RESET, BLU_FG, " ", RESET);
		return ;
	}
	c->prompt = ft_aconcat(20, WHT_FG, "",
			WHT_BG, BLK_FG, BOLD, " ", c->weather_emoji, " ", WHT_FG, RED_BG,
			" ", "Minishell ", path, " ", status, " ", RESET,
			RED_FG, " ", RESET);
}

static void	ctx_init(t_ctx *c, char **env)
{
	c->gbc = gb_init();
	c->env = create_env(c, env);
	if (!c->gbc)
		exit_shell(c, 1);
	c->return_code = 0;
	c->weather_emoji = gb_calloc(5, sizeof(char), PERM_GB, &c->gbc);
	c->env_list = env;
	get_weather(c);
	c->prompt = malloc(0);
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
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	ctx_init(&c, env);
	printf("Minishell ready\n");
	init_history(&c);
	termios_init(&c);
	while (true)
	{
		termios_set(&c, 0);
		c.entry = gb_add(readline(c.prompt), &c.gbc, CMD_GB);
		if (!c.entry)
			exit_shell(&c, 0);
		if (c.entry && ft_strlen(c.entry) != 0)
		{
			history(&c);
			if (exec_builtin(&c))
				continue ;
			if (ft_eq(c.entry, "here", 0))
				create_heredoc(&c);
			else
			{
				create_table(&c, table, gb_split(&c, c.entry, ' '));
				exec(&c, table);
			}
			gen_prompt(&c, format_path(&c), get_branch(&c));
			gb_delete(&c.gbc, CMD_GB);
		}
	}
}
