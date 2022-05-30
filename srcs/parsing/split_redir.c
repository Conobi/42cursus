/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:16:53 by conobi            #+#    #+#             */
/*   Updated: 2022/05/30 19:27:39 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_viewer(char **arrstr)
{
	int	i;

	i = -1;
	printf("Liste des strings: \n");
	while (arrstr[++i])
		printf("{%d: %s}\n", i, arrstr[i]);
}

// int	redir_count(char *str)
// {
// 	int	cnt;
// 	int	i;

// 	if (*str == '\'' || *str == '"')
// 		return (0);
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == '' && str[i + 1])
// 	}
// 	return (cnt);
// }

typedef struct s_split
{
	char	**arr;
	int		index;
	int		i;
	int		j;
	int		tokens_nb;
}	t_split;

static char	**split_redir_2(t_ctx *c, char **quotes)
{
	t_split	s;

	s = (t_split){0, -1, -1, -1, c->parser.len * 3};

	s.arr = gb_calloc(s.tokens_nb, sizeof(char), REDIR_GB, &c->gbc);
	while (quotes[++s.i])
	{
		if (quotes[s.i][0] == '\'' || quotes[s.i][0] == '"')
		{
			s.arr[++s.j] = gb_add(ft_strdup(quotes[s.i]), &c->gbc, REDIR_GB);
		}
		// else
		// {
		// 	s.arr[++s.j] = gb_calloc(600, sizeof(char), REDIR_GB, &c->gbc);
		// 	s.arr[s.j] = "Wow mais c'est génial ici!";
		// }
	}
	return (s.arr);
}

char **split_redir(t_ctx *c, char **quotes)
{
	char	**tamerelapute;

	reset_quote_bool(c);
	tamerelapute = split_redir_2(c, quotes);
	split_viewer(tamerelapute);
	return (tamerelapute);
}
