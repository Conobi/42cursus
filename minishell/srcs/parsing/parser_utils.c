/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:26:47 by conobi            #+#    #+#             */
/*   Updated: 2022/08/11 17:29:30 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_quote_bool(t_ctx *c, char curr)
{
	if (curr == '\'' && c->parser.dquoted == false)
		c->parser.squoted = !c->parser.squoted;
	if (curr == '"' && c->parser.squoted == false)
		c->parser.dquoted = !c->parser.dquoted;
}

void	reset_quote_bool(t_ctx *c)
{
	c->parser.squoted = false;
	c->parser.dquoted = false;
}

int	is_curr_quoted(t_ctx *c)
{
	if (c->parser.squoted == false && c->parser.dquoted == false)
		return (0);
	else
		return (1);
}

int	token_type(char *str)
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

void	syntax_err(t_ctx *c, char *token)
{
	char	*err;

	err = sf_add(
			ft_aconcat(3, "syntax error near unexpected token `", token, "'"),
			&c->gbc,
			CMD_GB
			);
	create_error(c, (t_error){WARNING, SHELL_NAME, err, NULL, 258, 0});
}
