/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:50:09 by conobi            #+#    #+#             */
/*   Updated: 2022/01/16 15:38:20 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	perr_print(char *str)
{
	perror(str);
	return (1);
}

int	main(int argc, char *argv[], char *env[])
{
	pid_t	pid;
	int		status;

	if (argc > 1)
	{
		pid = fork();
		if (pid == -1)
			return (perr_print("fork"));
		else if (pid == 0 && execve(argv[1], argv + 1, env) == -1)
			perror("execve");
		else
		{
			wait(&status);
			printf("Je suis le père, et mon pid = %d. Le pid de mon fils = %d\n",
				getpid(), pid);
		}
	}
	return (0);
}
