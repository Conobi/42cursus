/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:57:41 by abastos           #+#    #+#             */
/*   Updated: 2022/06/16 17:24:14 by abastos          ###   ########lyon.fr   */
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
# include <termios.h>
# include <signal.h>
# include <dirent.h>
# include "../libft/libft.h"
// Linux required
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

int	g_return;

// To show the printf debug for parsing purpose
# define PDEBUG	0

//Term colors
# define RED_FG	"\e[91m"
# define GRN_FG	"\e[32m"
# define YEL_FG	"\e[33m"
# define BLU_FG	"\e[34m"
# define MAG_FG	"\e[35m"
# define CYN_FG	"\e[36m"
# define WHT_FG	"\e[37m"
# define BLK_FG	"\e[30m"
# define ACC_FG	"\e[38;2;65;208;117m"

# define RED_BG	"\e[101m"
# define GRN_BG	"\e[42m"
# define YEL_BG	"\e[43m"
# define BLU_BG	"\e[44m"
# define MAG_BG	"\e[45m"
# define CYN_BG	"\e[46m"
# define WHT_BG	"\e[47m"
# define BLK_BG	"\e[40m"
# define ACC_BG	"\e[48;2;65;208;117m"

# define RESET	"\e[0m"
# define BOLD	"\e[1m"

# define OTHR_TK	0
# define OUT_TK		1
# define IN_TK		2
# define APPD_TK	3
# define HRDC_TK	4

// GARBAGE TYPE
# define PERM_GB	0
# define ENTRY_GB	1
# define PIPE_GB	2
# define QUOTE_GB	3
# define REDIR_GB	4
# define CMD1P_GB	5
# define CMD_GB		6

// todo: Use ds_prompt settings to enable or disable prompt generation
# define DS_PROMPT	1

// Errors
# define FILE_ERR 	1
# define ERROR		2
# define WARNING	3

typedef struct s_redir {
	char	*arg;
	short	type;
}	t_redir;

typedef struct s_ncommand {
	int		argc;
	char	**argv;
	int		redc;
	t_redir	*redirections;
	char	*exec_path;
	int		outfile;
	int		infile;
}	t_ncommand;

typedef struct s_parser {
	char	squoted;
	char	dquoted;
	char	**pipes;
	char	***split;
	int		pipes_n;
	int		len;
}	t_parser;

typedef struct s_exec {
	pid_t	*process;
	int		*pipe_fd;
}	t_exec;

typedef struct s_ctx {
	struct s_ncommand	*cmds;
	struct termios		term;
	struct termios		base;
	t_garbc				*gbc;
	t_list				*env;
	t_parser			parser;
	t_exec				*exec;
	char				**env_list;
	char				*prompt;
	char				*entry;
	char				*weather_emoji;
	char				*last_path;
	char				*last_entry;
	int					ncmds;
	int					return_code;
	int					history_fd;
}	t_ctx;

// Utils
void		exit_shell(t_ctx *c, int code);

// Parsing
void		parser(t_ctx *c);
void		pipe_cutter(t_ctx *c);
void		set_quote_bool(t_ctx *c, char curr);
void		reset_quote_bool(t_ctx *c);
int			is_curr_quoted(t_ctx *c);
char		**split_quote(t_ctx *c, char *str);
char		**split_redir(t_ctx *c, char **split);
t_ncommand	cmd_create(t_ctx *c, char **split);

typedef struct s_error {
	short	type;
	char	*cmd;
	char	*message;
	char	*path;
	int		code;
	bool	is_file;
}	t_error;

typedef struct s_env {
	char	*key;
	char	*value;
}	t_env;

// Executor functions
void		exec(t_ctx *c);
void		outfile_handler(t_ctx *c, int curr_cmd);
void		infile_handler(t_ctx *c, int curr_cmd);
void		close_pipes(t_ctx *c, int pipes);
void		switch_pipes(int in, int out);
bool		set_exec_path(t_ctx *c);
void		in_selector(t_ctx *c, int curr, int *in);
void		out_selector(t_ctx *c, int curr,
				int piped_commands, int *out);
char		*find_exec(t_ctx *c, const char *exec_name);
int			create_heredoc(t_ctx *c, char *stop);

// Builtins
bool		exec_builtin(t_ctx *c, t_ncommand cmd);
void		b_cd(t_ctx *c, char *path);
void		b_pwd(t_ctx *c);
void		b_echo(t_ncommand cmd);
void		b_ls(t_ctx *c, int cmd);
void		rl_replace_line(const char *text, int clear_undo);

// Utils
void		exit_shell(t_ctx *c, int code);
char		*get_path(t_ctx *c);
char		*format_path(t_ctx *c);
bool		error_handler(t_ctx *c, t_error err);
void		gen_prompt(t_ctx *c, const char *path, const char *branch);
void		history(t_ctx *c);
void		init_history(t_ctx *c);
char		*get_branch(t_ctx *c);
void		get_weather(t_ctx *c);
t_list		*create_env(t_ctx *c, char **env);
void		termios_init(t_ctx *c);
void		termios_set(t_ctx *c, short mode);
void		create_error(t_ctx *c, t_error err);

// Signal handlers
void		fork_sig_handler(int sig);
void		sig_handler(int sig);
void		heredoc_sig_handler(int sig);

#endif
