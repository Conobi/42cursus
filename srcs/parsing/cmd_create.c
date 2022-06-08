/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:42:22 by conobi            #+#    #+#             */
/*   Updated: 2022/06/08 17:20:45 by conobi           ###   ########lyon.fr   */
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

static int	token_type(char *str)
{
	if (ft_eq(str, ">", 0))
		return (OUT_TK);
	else if (ft_eq(str, "<", 0))
		return (IN_TK);
	else if (ft_eq(str, ">>", 0))
		return (APPD_TK);
	else if (ft_eq(str, "<<", 0))
		return (HRDC_TK);
	return (OTHR_TK);
}

typedef struct s_builder
{
	int			nb_tokens;
	int			i;
	int			j;
	int			k;
}	t_builder;

static void	cmd_create_alg(t_ctx *c, t_builder *b,
		char **split, t_ncommand *cmd)
{
	if (token_type(split[b->i])
		&& split[b->i + 1] && !token_type(split[b->i + 1]))
	{
		cmd->redirections[++b->j].arg = gb_add(ft_strdup(split[b->i + 1]),
				&c->gbc, CMD1P_GB);
		cmd->redirections[b->j].type = token_type(split[b->i]);
		b->i++;
		return ;
	}
	cmd->argv[++b->k] = gb_add(ft_strdup(split[b->i]),
			&c->gbc, CMD1P_GB);
}

t_ncommand	cmd_create(t_ctx *c, char **split)
{
	t_ncommand	cmd;
	t_builder	b;

	b = (t_builder){0, -1, -1, -1};
	while (split[b.nb_tokens])
		b.nb_tokens++;
	cmd.redirections = gb_calloc(b.nb_tokens + 1, sizeof(t_redir),
			CMD1P_GB, &c->gbc);
	cmd.argv = gb_calloc(b.nb_tokens + 1, sizeof(cmd.argv),
			CMD1P_GB, &c->gbc);
	while (split[++b.i])
		cmd_create_alg(c, &b, split, &cmd);
	cmd.redc = b.j + 1;
	cmd.argc = b.k + 1;
	cmd_viewer(cmd);
	return (cmd);
}
