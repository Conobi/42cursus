/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:06:17 by abastos           #+#    #+#             */
/*   Updated: 2022/09/26 19:57:27 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	overflow_atoi(const char *str)
{
	int		sign;
	long	r;

	r = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		r = r * 10 + *str - '0';
		str++;
	}
	return ((int)r * sign);
}

static int	valid_param(char *s)
{
	int		i;
	bool	found_digit;
	bool	not_digit_anymore;

	i = 0;
	found_digit = false;
	not_digit_anymore = false;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (ft_isdigit(s[i]) || (s[i] == '-' && ft_isdigit(s[++i])))
		found_digit = true;
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
			not_digit_anymore = true;
		else if (
			(ft_isdigit(s[i]) && not_digit_anymore)
			|| !(ft_isdigit(s[i]) || s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		)
			return (false);
		i++;
	}
	if (found_digit)
		return (true);
	return (false);
}

static int	usual_exit(t_ctx *c, t_ncommand cmd)
{
	if (!valid_param(cmd.argv[1]))
	{
		printf("exit\n");
		create_error(c, (t_error){WARNING, "exit",
			"numeric argument required", cmd.argv[1], 255, false});
		exit_shell(c, 255, true);
		return (255);
	}
	if (cmd.argc > 2)
	{
		printf("exit\n");
		create_error(c, (t_error){WARNING, "exit",
			"too many arguments", NULL, 1, false});
		return (1);
	}
	exit_shell(c, overflow_atoi(cmd.argv[1]) % 256, true);
	return (0);
}

int	b_exit(t_ctx *c, t_ncommand cmd)
{
	close_pipes(c, 2 * c->ncmds);
	if (cmd.argc > 1 && c->ncmds <= 1)
		return (usual_exit(c, cmd));
	else if (c->ncmds > 1)
	{
		if (cmd.argc == 2 && valid_param(cmd.argv[1]))
			return (overflow_atoi(cmd.argv[1]) % 256);
	}
	else
		exit_shell(c, g_return, false);
	return (0);
}

/**
 * @brief This function is a clone of exit command for builtins
 *
 * @param c Minishell context struct
 * @param code Exit code
 * @param no_print Disable print statement
 */
void	exit_shell(t_ctx *c, int code, int no_print)
{
	if (!no_print)
		printf("exit\n");
	fdgb_close_all(&c->fdgbc);
	gb_clear(&c->gbc);
	exit(code);
}
