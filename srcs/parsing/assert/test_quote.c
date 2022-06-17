/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:21:18 by conobi            #+#    #+#             */
/*   Updated: 2022/06/17 15:23:49 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short	test_quote(t_ctx *c)
{
	char	*cur;

	cur = c->entry;
	reset_quote_bool(c);
	while (*cur)
	{
		set_quote_bool(c, *cur);
		cur++;
	}
	if (c->parser.squoted == -1 && c->parser.dquoted == -1)
		return (1);
	if (c->parser.squoted == 1)
		syntax_err(c, "'");
	if (c->parser.dquoted == 1)
		syntax_err(c, "\"");
	return (0);
}
