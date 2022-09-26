/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:42:22 by conobi            #+#    #+#             */
/*   Updated: 2022/09/26 16:27:30 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_temp
{
	int			nb_tokens;
	int			i;
	int			j;
	int			k;
}	t_temp;

/*
	Si une redirection est trouvée et est suivie par un string qui n'est pas
	une redirection, dans ce cas on l'ajoute et on la déclare. Sinon, on
	ajoute le token à argc/argv.
*/
static void	cmd_create_alg(t_ctx *c, t_temp *t,
		char **split, t_ncommand *cmd)
{
	if (token_type(split[t->i])
		&& split[t->i + 1] && !token_type(split[t->i + 1]))
	{
		cmd->redirections[++t->j].arg = sf_add(ft_strdup(split[t->i + 1]),
				&c->gbc, CMD1P_GB);
		cmd->redirections[t->j].type = token_type(split[t->i]);
		t->i++;
		return ;
	}
	cmd->argv[++t->k] = sf_add(ft_strdup(split[t->i]),
			&c->gbc, CMD1P_GB);
}

/*
	Permet de trier les tokens entre arguments et redirections,
	et d'initialiser la commande.
*/
t_ncommand	cmd_create(t_ctx *c, char **split)
{
	t_ncommand	cmd;
	t_temp		t;

	t = (t_temp){-1, -1, -1, -1};
	while (split[++t.nb_tokens])
		;
	cmd.redirections = sf_calloc(t.nb_tokens + 1, sizeof(t_redir),
			CMD_GB, &c->gbc);
	cmd.argv = sf_calloc(t.nb_tokens + 1, sizeof(char *),
			CMD_GB, &c->gbc);
	while (split[++t.i])
		cmd_create_alg(c, &t, split, &cmd);
	cmd.redc = t.j + 1;
	cmd.argc = t.k + 1;
	cmd.exec_path = NULL;
	cmd.is_builtins = false;
	cmd.errored = false;
	gb_delete(&c->gbc, REDIR_GB);
	return (cmd);
}
