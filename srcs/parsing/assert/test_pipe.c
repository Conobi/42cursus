/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:21:18 by conobi            #+#    #+#             */
/*   Updated: 2022/06/17 15:17:04 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// typedef struct s_error {
// 	short	type;
// 	char	*cmd;
// 	char	*message;
// 	char	*path;
// 	int		code;
// 	bool	is_file;
// }	t_error;

// # define OTHR_TK	0
// # define OUT_TK		1
// # define IN_TK		2
// # define APPD_TK	3
// # define HRDC_TK	4

short	test_pipe(t_ctx *c)
{
	int	i;

	i = -1;
	if (c->ncmds > 1)
	{
		while (++i < c->ncmds)
		{
			if (c->cmds[i].argc == 0 && c->cmds[i].redc == 0)
			{
				syntax_err(c, "|");
				return (0);
			}
		}
	}
	return (1);
}
