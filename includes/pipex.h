/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:47:32 by conobi            #+#    #+#             */
/*   Updated: 2022/01/17 19:31:58 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// # include <sys/types.h>
// # include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "libft.h"

/* structures.c */
typedef struct s_data {
	char	*cmd1_path;
	char	*cmd2_path;
	int		in_fd;
	int		out_fd;
}	t_data;

/* utils.c */
int		perr_print(char *str);
char	*find_binary_path(char *binary, char **env);

#endif
