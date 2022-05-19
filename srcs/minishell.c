/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:59:50 by abastos           #+#    #+#             */
/*   Updated: 2022/05/19 20:30:51 by abastos          ###   ########lyon.fr   */
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
 * @brief This function is used to handle unix signals with the provided sig code
 *
 * @param sig Signal code
 */
void	sig_handler(int sig)
{
	//todo: clear buffer
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (sig == SIGQUIT)
		return ;
	if (sig == SIGKILL)
	{
		printf("exit\n");
		exit(1);
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
	char	*status;

	free(c->prompt);
	printf("%d -> %d\n", c->return_code, WEXITSTATUS(c->return_code));
	if (WEXITSTATUS(c->return_code) == 0)
		status = "✓";
	else
		status = gb_add(ft_strjoin("✖ ",
					gb_add(ft_itoa(WEXITSTATUS(c->return_code)),
						&c->gbc, CMD_GB)), &c->gbc, CMD_GB);
	if (branch)
	{
		c->prompt = ft_aconcat(25, WHT_FG, "",
				WHT_BG, BLK_FG, BOLD, "  ", WHT_FG, RED_BG,
				" ", "Minishell ", path, " ", status, " ",
				RED_FG, BLU_BG, " ", WHT_FG,
				"⚡️git:(", branch, ") ", RESET, BLU_FG, " ", RESET);
		return ;
	}
	c->prompt = ft_aconcat(18, WHT_FG, "",
			WHT_BG, BLK_FG, BOLD, "  ", WHT_FG, RED_BG,
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
	gen_prompt(c, format_path(c), get_branch(c));
	c->last_path = get_path(c);
	c->history_fd = open("./.minishell_history",
			O_CREAT | O_RDWR, 0000644);
	c->last_entry = NULL;
	c->parser.squoted = -1;
	c->parser.dquoted = -1;
	c->env_list = env;
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
	// get_weather(&c);
	// char	*args[2];
	// args[0] = "https://kiyo.ooo/f/meteoshell.php";
	// args[1] = "-k";
	// printf("%s -> %s : %s\n", find_exec(&c, "curl"), args[0], args[1]);
	// execve(find_exec(&c, "curl"), args, c.env_list);
	// printf("%c -> %d\n", c.weather_emoji, c.return_code);
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
				if (exec_builtin(&c))
					continue ;
				else
				{
					create_table(&c, table, gb_split(&c, c.entry, ' '));
					exec(&c, table);
				}
			}
			gen_prompt(&c, format_path(&c), get_branch(&c));
			gb_delete(&c.gbc, CMD_GB);
		}
		else
			sig_handler(SIGKILL);
	}
}
