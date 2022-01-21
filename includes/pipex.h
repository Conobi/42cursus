/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 14:47:32 by conobi            #+#    #+#             */
/*   Updated: 2022/01/21 17:40:39 by conobi           ###   ########lyon.fr   */
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
	char	**env;
	char	**cmd1_args;
	char	**cmd2_args;
	int		in_fd;
	int		out_fd;
	int		piped[2];
	int		status;
}	t_data;

/* utils.c */
int		perr_print(char *str);
int		perr_cb(char *errstr, int ret, int ver);
char	*find_binary_path(char *binary, t_data *data);
void	slice_binary_args(char *cmd1, char *cmd2, t_data *data);

#endif
