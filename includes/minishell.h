/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:57:41 by abastos           #+#    #+#             */
/*   Updated: 2022/05/11 19:59:49 by conobi           ###   ########lyon.fr   */
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
# define RED_FG	"[91m"
# define GRN_FG	"[32m"
# define YEL_FG	"[33m"
# define BLU_FG	"[34m"
# define MAG_FG	"[35m"
# define CYN_FG	"[36m"
# define WHT_FG	"[37m"
# define BLK_FG	"[30m"

# define RED_BG	"[101m"
# define GRN_BG	"[42m"
# define YEL_BG	"[43m"
# define BLU_BG	"[44m"
# define MAG_BG	"[45m"
# define CYN_BG	"[46m"
# define WHT_BG	"[47m"
# define BLK_BG	"[40m"
# define RESET	"[0m"
# define BOLD	"[1m"

// GARBAGE TYPE
# define PERM_GB	0
# define ENTRY_GB	1
# define PIPE_GB	1

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

typedef struct s_parser {
	char	squoted;
	char	dquoted;
	char	**quotes;
} t_parser;

typedef struct s_ctx {
	t_garbc				*gbc;
	char				*prompt;
	char				*entry;
	t_parser			parser;
	struct s_command	*command_table;
}	t_ctx;

typedef struct s_table {
	int					commands_num;
	struct s_command	*command_table;
	pid_t				*process;
	int					cmd_idx;
	int					*pipe_fd;
}	t_table;

void	add_args(char *arg);
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

// Utils
void	exit_shell(t_ctx *c, int code);

// Parsing
void	parser(t_ctx *c);
void	pipe_cutter(t_ctx *c);

#endif
