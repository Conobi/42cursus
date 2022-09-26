/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:59:50 by abastos           #+#    #+#             */
/*   Updated: 2022/09/25 14:47:06 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_return = 0;

/**
 * @brief This function create the minishell prompt
 *
 * @param c Minishell context struct
 * @param argc Number of procss arguments
 * @param argv Process arguments list
 */
static void	prompt_init(t_ctx *c, int argc, char **argv)
{
	c->weather_emoji = sf_calloc(5, sizeof(char), PERM_GB, &c->gbc);
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
}

/**
 * @brief This function is used to create context for Minishell
 *
 * @param c Minishell context struct
 * @param env Env of parent process
 * @param argc Number of process arguments
 * @param argv Process arguments list
 */
static void	ctx_init(t_ctx *c, char **env, int argc, char **argv)
{
	t_env	*shlvl;

	g_return = 0;
	c->gbc = gb_init();
	c->fdgbc = fdgb_init();
	if (!c->gbc)
		create_error(c, (t_error){ERROR, SHELL_NAME, strerror(ENOMEM),
			NULL, ENOMEM, false});
	c->env = create_env(c, env);
	shlvl = get_env_by_key(c->env, "SHLVL");
	if (!shlvl || !shlvl->value)
		ft_lstadd_front(&c->env, create_env_entry(c, "SHLVL=1"));
	else
		shlvl->value = sf_add(ft_itoa(ft_atoi(shlvl->value) + 1),
				&c->gbc, PERM_GB);
	prompt_init(c, argc, argv);
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
		c.entry = sf_add(readline(c.prompt), &c.gbc, CMD_GB);
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
