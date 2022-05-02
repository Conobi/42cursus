/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:57:41 by abastos           #+#    #+#             */
/*   Updated: 2022/05/02 16:46:24 by conobi           ###   ########lyon.fr   */
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
# define RED_FG	"\x1B[91m"
# define GRN_FG	"\x1B[32m"
# define YEL_FG	"\x1B[33m"
# define BLU_FG	"\x1B[34m"
# define MAG_FG	"\x1B[35m"
# define CYN_FG	"\x1B[36m"
# define WHT_FG	"\x1B[37m"
# define BLK_FG	"\x1B[30m"

# define RED_BG	"\x1B[101m"
# define GRN_BG	"\x1B[42m"
# define YEL_BG	"\x1B[43m"
# define BLU_BG	"\x1B[44m"
# define MAG_BG	"\x1B[45m"
# define CYN_BG	"\x1B[46m"
# define WHT_BG	"\x1B[47m"
# define BLK_BG	"\x1B[40m"
# define RESET	"\x1B[0m"
# define BOLD	"\x1B[1m"

typedef struct s_command {
	int		args_num;
	char	**args;
	bool	piped;
	bool	heredoc;
	bool	append;
	char	**infiles;
	int		infile;
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
