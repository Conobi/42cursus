/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:57:41 by abastos           #+#    #+#             */
/*   Updated: 2022/06/27 20:31:03 by conobi           ###   ########lyon.fr   */
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

# define SHELL_NAME "Minishell"

// To show the printf debug for parsing purpose
# define PDEBUG	0
# define EDEBUG	0

//Term colors
# define RED_FG	"\033[91m"
# define GRN_FG	"\033[32m"
# define YEL_FG	"\033[33m"
# define BLU_FG	"\033[34m"
# define MAG_FG	"\033[35m"
# define CYN_FG	"\033[36m"
# define WHT_FG	"\033[37m"
# define BLK_FG	"\033[30m"
# define ACC_FG	"\033[38;2;65;208;117m"

# define RED_BG	"\033[101m"
# define GRN_BG	"\033[42m"
# define YEL_BG	"\033[43m"
# define BLU_BG	"\033[44m"
# define MAG_BG	"\033[45m"
# define CYN_BG	"\033[46m"
# define WHT_BG	"\033[47m"
# define BLK_BG	"\033[40m"
# define ACC_BG	"\033[48;2;65;208;117m"

# define RESET	"\033[0m"
# define BOLD	"\033[1m"

# define OTHR_TK	0
# define OUT_TK		1
# define IN_TK		2
# define APPD_TK	3
# define HRDC_TK	4

// GARBAGE TYPE
# define PERM_GB	0
# define CMD_GB		1
# define ENTRY_GB	2
# define PIPE_GB	3
# define QUOTE_GB	4
# define REDIR_GB	5
# define CMD1P_GB	6
# define CMD2P_GB	7
# define CMD3P_GB	8
# define CMD4P_GB	9
# define EXPT_PT_GB	10

// todo: Use ds_prompt settings to enable or disable prompt generation
# define DS_PROMPT	1

// Errors
# define FILE_ERR 	1
# define FATAL		2
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
short		parser(t_ctx *c);
void		split_pipe(t_ctx *c);
void		set_quote_bool(t_ctx *c, char curr);
void		reset_quote_bool(t_ctx *c);
int			is_curr_quoted(t_ctx *c);
char		**split_quote(t_ctx *c, char *str);
char		**split_redir(t_ctx *c, char **split);
t_ncommand	cmd_create(t_ctx *c, char **split);
void		enverr_pass(t_ctx *c);
void		envvar_pass(t_ctx *c);
void		remquote_pass(t_ctx *c);

// Tests
short		test_quote(t_ctx *c);
short		test_pipe(t_ctx *c);
short		test_redir(t_ctx *c);
void		syntax_err(t_ctx *c, char *token);

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
	bool	unset;
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

int			b_export(t_ctx *c, int argc, char **argv);
void		export_print(t_ctx *c);
int			b_env(t_ctx *c, int argc, char **argv);

// Utils
void		exit_shell(t_ctx *c, int code);
char		*get_path(t_ctx *c);
char		*format_path(t_ctx *c);
void		err_print(const char *err);
bool		error_handler(t_ctx *c, t_error err);
void		gen_prompt(t_ctx *c, const char *path, const char *branch);
void		history(t_ctx *c);
void		init_history(t_ctx *c);
char		*get_branch(t_ctx *c);
void		get_weather(t_ctx *c);
t_list		*create_env(t_ctx *c, char **env);
t_env		*get_env_by_key(t_list *head, char *key);
t_list		*get_env_list_by_key(t_list *head, char *key);
void		termios_init(t_ctx *c);
void		termios_set(t_ctx *c, short mode);
void		create_error(t_ctx *c, t_error err);

// Signal handlers
void		fork_sig_handler(int sig);
void		sig_handler(int sig);
void		heredoc_sig_handler(int sig);

#endif
