/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:59:50 by abastos           #+#    #+#             */
/*   Updated: 2022/06/09 19:49:57 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	(void) sig;
	return ;
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
	t_ctx	c;

	(void)argc;
	(void)argv;
	ctx_init(&c, env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	init_history(&c);
	termios_init(&c);
	while (true)
	{
		termios_set(&c, 0);
		c.entry = gb_add(readline(c.prompt), &c.gbc, CMD_GB);
		if (!c.entry)
			exit_shell(&c, 0);
		parser(&c);
		if (c.entry && ft_strlen(c.entry) != 0)
		{
			history(&c);
			if (exec_builtin(&c)) // todo: check in exec command for piped builtins
				continue ;
			exec(&c);
			gen_prompt(&c, format_path(&c), get_branch(&c));
			gb_delete(&c.gbc, CMD_GB);
		}
	}
}
