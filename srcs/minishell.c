/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:59:50 by abastos           #+#    #+#             */
/*   Updated: 2022/08/09 18:36:56 by conobi           ###   ########lyon.fr   */
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

	g_return = 0;
	c->gbc = gb_init();
	if (!c->gbc)
		exit_shell(c, 1, true); //todo: throw error when allocation failed
	c->env = create_env(c, env);
	shlvl = get_env_by_key(c->env, "SHLVL");
	if (!shlvl)
		ft_lstadd_front(&c->env, create_env_entry(c, "SHLVL=1"));
	else
		shlvl->value = gb_add(ft_itoa(ft_atoi(shlvl->value) + 1), &c->gbc, PERM_GB);
	c->weather_emoji = gb_calloc(5, sizeof(char), PERM_GB, &c->gbc);
	c->weather_emoji = gb_calloc(5, sizeof(char), PERM_GB, &c->gbc);
	c->better_prompt = true;
	if (argc >= 2 && ft_eq(argv[1], "safe_prompt", 0))
		c->better_prompt = false;
	if (c->better_prompt)
		get_weather(c);
	c->prompt = malloc(0);
	if (c->better_prompt)
		gen_prompt(c, format_path(c), get_branch(c));
	else
		gen_sad_prompt(c, format_path(c));
	c->last_entry = NULL;
	c->parser.squoted = -1;
	c->parser.dquoted = -1;
	c->heredoc_errored = NULL;
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
			exit_shell(&c, 0, false);
		if (parser(&c))
		{
			exec(&c);
			if (c.better_prompt)
				gen_prompt(&c, format_path(&c), get_branch(&c));
			else
				gen_sad_prompt(&c, format_path(&c));
			gb_delete(&c.gbc, CMD_GB);
		}
		else
			g_return = 258;
	}
}
