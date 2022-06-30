/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:21:18 by conobi            #+#    #+#             */
/*   Updated: 2022/06/30 17:13:57 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Permet de tester la présence de quotes non fermées.
	Elle permet de se comporter différemment de bash, qui gère les quotes non
	fermées comme des heredocs.
*/
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
