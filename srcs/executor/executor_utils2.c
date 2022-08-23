/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:20:15 by abastos           #+#    #+#             */
/*   Updated: 2022/08/23 19:05:06 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_by_path_env(t_ctx *c, const char *exec_name)
{
	t_env	*env_path;
	char	**path;
	char	*exec_path;
	int		i;

	env_path = get_env_by_key(c->env, "PATH");
	if (!env_path || !ft_strlen(env_path->value) || !env_path->value)
	{
		create_error(c, (t_error){WARNING, SHELL_NAME,
			"No such file or directory", (char *)exec_name, 127, true});
		return (NULL);
	}
	path = gb_split(env_path->value, ':', &c->gbc, CMD_GB);
	if (!path)
		enomem_error(&c->gbc);
	i = -1;
	while (path[++i])
	{
		exec_path = sf_add(
				ft_aconcat(3, path[i], "/", exec_name),
				&c->gbc, CMD_GB);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
	}
	return (NULL);
}

/**
 * @brief This function is used to find an executable in PATH env variable
 * or given path for the given exec_name
 *
 * @param c Minishell context struct
 * @param exec_name executable name to search
 * @return char* Returns the executable path
 */
char	*find_exec(t_ctx *c, const char *exec_name)
{
	char	*path;
	t_env	*path_env;

	if (ft_strchr(exec_name, '/')
		|| ft_eq(exec_name, ".", 0) || ft_eq(exec_name, "..", 0))
	{
		if (file_errors(c, (t_error){FILE_ERR, SHELL_NAME, NULL,
				(char *)exec_name, 1, true}))
			return (NULL);
		return ((char *)exec_name);
	}
	path = find_by_path_env(c, exec_name);
	if (path)
		return (path);
	path_env = get_env_by_key(c->env, "PATH");
	if (path_env && path_env->value && ft_strlen(path_env->value))
		create_error(c, (t_error){WARNING, SHELL_NAME,
			"command not found", (char *)exec_name, 127, true});
	return (NULL);
}

/**
 * @brief This function is used to determine and set
 * input and output redirection for a command
 *
 * @param c Minishell context struct
 * @param curr Index of current command
 * @param in Pointer to infile fd to modify for input
 * @param out Pointer to output fd to modify for output
 */
void	io_handler(t_ctx *c, int curr, int *in, int *out)
{
	infile_handler(c, curr);
	outfile_handler(c, curr);
	in_selector(c, curr, in);
	out_selector(c, curr, out);
}
