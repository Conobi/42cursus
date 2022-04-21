/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:57:41 by abastos           #+#    #+#             */
/*   Updated: 2022/03/30 16:30:02 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <fcntl.h>
# include "../libft/libft.h"

//Term colors
# define RED	"\x1B[31m"
# define GRN	"\x1B[32m"
# define YEL	"\x1B[33m"
# define BLU	"\x1B[34m"
# define MAG	"\x1B[35m"
# define CYN	"\x1B[36m"
# define WHT	"\x1B[37m"
# define RESET	"\x1B[0m"

typedef struct s_command {
	int		args_num;
	char	**args;
	bool	piped;
	bool	heredoc;
	char	**infiles;
	int		infile;
	bool	append;
	char	**outfiles;
	int		outfile;
	char	*exec_path;
}	t_command;
void	add_args(char *arg);

typedef struct s_table {
	int					commands_num;
	struct s_command	*command_table;
	pid_t				*process;
	int					cmd_idx;
	int					*pipe_fd;
}	t_table;

void	add_command(t_command *command);

// Executor functions
void	exec(t_table *table);
char	*find_exec(char *exec_name);
void	outfile_handler(t_table *table, int curr_cmd);
void	close_pipes(t_table *table, int pipes);
void	switch_pipes(int in, int out);
void	set_exec_path(t_table *table);
void	in_selector(t_table *table, int curr, int *in);
void	out_selector(t_table *table, int curr, int piped_commands, int *out);

// Shell subsystem
void	exit_shell(t_table *table);

#endif
