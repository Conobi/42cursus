/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:57:41 by abastos           #+#    #+#             */
/*   Updated: 2022/05/12 00:44:51 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

// Term colors
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

// GARBAGE TYPE
# define PERM_GB	0
# define PIPE_GB	1
# define CMD_GB		2

// Errors
# define FILE_ERR 	1

/**
 * @brief Struct for a command object
 */
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

typedef struct s_parser {
	char	squoted;
	char	dquoted;
	char	**quotes;
}	t_parser;

typedef struct s_ctx {
	t_garbc				*gbc;
	char				*prompt;
	char				*entry;
	t_parser			parser;
	struct s_command	*command_table;
}	t_ctx;

typedef struct s_error {
	short	type;
	char	*cmd;
	char	*path;
	int		code;
}	t_error;

void	add_command(t_command *command);

// Executor functions
void	exec(t_ctx *c, t_table *table);
void	outfile_handler(t_table *table, int curr_cmd);
void	close_pipes(t_table *table, int pipes);
void	switch_pipes(int in, int out);
void	set_exec_path(t_ctx *c, t_table *table);
void	in_selector(t_table *table, int curr, int *in);
void	out_selector(t_table *table, int curr, int piped_commands, int *out);

// Builtins
void	b_cd(t_ctx *c, char *path);
void	b_pwd(void);
void	b_echo(const char *args);

// Utils
void	exit_shell(t_table *table, t_ctx *c, int code);
char	*get_path(t_ctx *c);
bool	error_handler(t_ctx *c, t_error err);
void	gen_prompt(t_ctx *c, const char *path);
void	history(t_ctx *c);

#endif
