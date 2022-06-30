/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:59:50 by abastos           #+#    #+#             */
/*   Updated: 2022/06/30 15:54:32 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_return = 0;

/**
 * @brief This function is used to create context for Minishell
 *
 * @param c Minishell context struct
 * @param env Env of parent process
 * @param argc Number of arguments
 * @param argv Arguments list
 */
static void	ctx_init(t_ctx *c, char **env, int argc, char **argv)
{
	t_env	*shlvl;

	c->gbc = gb_init();
	if (!c->gbc)
		exit_shell(c, 1);
	c->env = create_env(c, env);
	shlvl = get_env_by_key(c->env, "SHLVL");
	shlvl->value = gb_add(ft_itoa(ft_atoi(shlvl->value) + 1), &c->gbc, PERM_GB);
	c->weather_emoji = gb_calloc(5, sizeof(char), PERM_GB, &c->gbc);
	c->env_list = env;
	c->weather_emoji = gb_calloc(5, sizeof(char), PERM_GB, &c->gbc);
	c->env_list = env;
	get_weather(c);
	c->better_prompt = true;
	if (argc == 2 && ft_atoi(argv[1]) == 0)
		c->better_prompt = false;
	c->prompt = malloc(0);
	if (c->better_prompt)
		gen_prompt(c, format_path(c), get_branch(c));
	else
		gen_sad_prompt(c, format_path(c), get_branch(c));
	c->history_fd = open("./.minishell_history", O_CREAT | O_RDWR, 0000644);
	c->last_entry = NULL;
	c->parser.squoted = -1;
	c->parser.dquoted = -1;
}

/**
 * @brief Main function of Minishell
 * @param env Env of parent process
 */
int	main(int argc, char **argv, char **env)
{
	t_ctx	c;

	ctx_init(&c, env, argc, argv);
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
		if (parser(&c))
		{
			exec(&c);
			if (c.better_prompt)
				gen_prompt(&c, format_path(&c), get_branch(&c));
			else
				gen_sad_prompt(&c, format_path(&c), get_branch(&c));
			gb_delete(&c.gbc, CMD_GB);
		}
		else
			g_return = 258;
	}
}
