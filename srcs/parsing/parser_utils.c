/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:26:47 by conobi            #+#    #+#             */
/*   Updated: 2022/05/17 19:52:16 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_quote_bool(t_ctx *c, char curr)
{
	if (curr == '\'' && c->parser.dquoted == -1)
		c->parser.squoted *= -1;
	if (curr == '"' && c->parser.squoted == -1)
		c->parser.dquoted *= -1;
}

void	reset_quote_bool(t_ctx *c)
{
	c->parser.squoted = -1;
	c->parser.dquoted = -1;
}

int	is_curr_quoted(t_ctx *c)
{
	if (c->parser.squoted == -1 && c->parser.dquoted == -1)
		return (0);
	else
		return (1);
}
