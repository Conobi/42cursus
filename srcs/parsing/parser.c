/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:11:57 by conobi            #+#    #+#             */
/*   Updated: 2022/06/09 20:12:47 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_viewer(t_ncommand cmd)
{
	int	i;

	if (PDEBUG != 1)
		return ;
	printf("-----------------\n");
	printf("argc: %d\n", cmd.argc);
	printf("argv: \n");
	i = -1;
	while (cmd.argv[++i])
		printf("\t[%d] {%s}\n", i, cmd.argv[i]);
	printf("redc: %d\n", cmd.redc);
	i = -1;
	while (++i < cmd.redc)
		printf("\t[%d] (%d) {%s}\n", i,
			cmd.redirections[i].type, cmd.redirections[i].arg);
}

static void	parse_print(t_ctx *c)
{
	if (PDEBUG != 1)
		return ;
	printf("Jacques a dit: [%s] (%d)\n", c->entry, (int)c->entry[0]);
}

static void	multi_viewer(char **pipes, int cnt)
{
	int	i;

	i = -1;
	if (PDEBUG != 1)
		return ;
	printf("Liste des pipes: \n");
	while (++i < cnt && pipes[i])
		printf("{%d: %s}\n", i, pipes[i]);
}

void	parser_init(t_ctx *c)
{
	if (!c->entry
		|| !ft_strncmp(c->entry, "exit", 5)
		|| !ft_strncmp(c->entry, "bye", 3))
		exit_shell(c, 0);
	c->parser.len = ft_strlen(c->entry);
	c->parser.squoted = -1;
	c->parser.dquoted = -1;
}

void	parser(t_ctx *c)
{
	int	i;

	parser_init(c);
	pipe_cutter(c);
	multi_viewer(c->parser.pipes, c->parser.pipes_n);
	if (PDEBUG)
		printf("-----------------\n");
	c->ncmds = -1;
	while (c->parser.pipes[++c->ncmds])
		;
	c->cmds = gb_calloc(c->ncmds + 1, sizeof(t_ncommand), QUOTE_GB, &c->gbc);
	i = -1;
	while (++i < c->ncmds)
		c->cmds[i] = cmd_create(c, split_redir(c,
					split_quote(c, c->parser.pipes[i])));
	i = -1;
	enverr_pass(c);
	envvar_pass(c);
	while (PDEBUG && ++i < c->ncmds)
		cmd_viewer(c->cmds[i]);
	if (PDEBUG)
		printf("-----------------\n");
	parse_print(c);
}
