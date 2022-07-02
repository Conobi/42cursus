/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:57:41 by abastos           #+#    #+#             */
/*   Updated: 2022/07/02 14:17:47 by conobi           ###   ########lyon.fr   */
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
# define ECHOCTL 0001000

# define SHELL_NAME "Minishell"

// To show the printf debug for parsing purpose
# define PDEBUG	0
# define EDEBUG	0

//Term colors
# define RED_FG	"\001\033[91m\002"
# define GRN_FG	"\001\033[32m\002"
# define YEL_FG	"\001\033[33m\002"
# define BLU_FG	"\001\033[34m\002"
# define MAG_FG	"\001\033[35m\002"
# define CYN_FG	"\001\033[36m\002"
# define WHT_FG	"\001\033[37m\002"
# define BLK_FG	"\001\033[30m\002"
# define ACC_FG	"\001\033[38;2;65;208;117m\002"

# define RED_BG	"\001\033[101m\002"
# define GRN_BG	"\001\033[42m\002"
# define YEL_BG	"\001\033[43m\002"
# define BLU_BG	"\001\033[44m\002"
# define MAG_BG	"\001\033[45m\002"
# define CYN_BG	"\001\033[46m\002"
# define WHT_BG	"\001\033[47m\002"
# define BLK_BG	"\001\033[40m\002"
# define ACC_BG	"\001\033[48;2;65;208;117m\002"

# define RESET	"\001\033[0m\002"
# define BOLD	"\001\033[1m\002"

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
	int		heredoc;
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
	bool				better_prompt;
	char				*prompt;
	char				*entry;
	char				*weather_emoji;
	char				*last_path;
	char				*last_entry;
	char				*heredoc_errored;
	int					ncmds;
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
int			token_type(char *str);
char		**split_quote(t_ctx *c, char *str);
char		**split_redir(t_ctx *c, char **split);
t_ncommand	cmd_create(t_ctx *c, char **split);
void		enverr_pass(t_ctx *c);
void		envvar_pass(t_ctx *c);
void		tilde_pass(t_ctx *c);
void		remquote_pass(t_ctx *c);

// Tests
short		test_quote(t_ctx *c);
short		test_pipe(t_ctx *c);
short		test_redir(t_ctx *c);
void		syntax_err(t_ctx *c, char *token);

/**
 * @brief Error struct
 * @param short type : type of error
 * @param char *cmd : cmd created error
 * @param char *msg : error message
 * @param char *path : a path to display in error message if needed
 * @param int code : error code to return
 * @param bool is_file : if given path must be a file or not
 */
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
void		io_handler(t_ctx *c, int curr, int *in, int *out);
void		close_pipes(t_ctx *c, int pipes);
void		switch_pipes(int in, int out);
char		*find_exec(t_ctx *c, const char *exec_name);
int			set_exec_path(t_ctx *c, t_ncommand *cmd);
int			open_heredocs(t_ctx *c);
int			create_heredoc(t_ctx *c, const char *stop);
void		child_status(int status);

// Builtins
bool		is_builtin(t_ncommand cmd);
int			exec_builtin(t_ctx *c, t_ncommand cmd);
int			b_cd(t_ctx *c, char *path);
int			b_pwd(t_ctx *c);
int			b_echo(t_ncommand cmd);
int			b_ls(t_ctx *c, int cmd);
void		exit_shell(t_ctx *c, int code);

int			b_export(t_ctx *c, int argc, char **argv);
void		export_print(t_ctx *c);
int			b_env(t_ctx *c, int argc);
int			b_unset(t_ctx *c, int argc, char **argv);

// Utils
void		rl_replace_line(const char *text, int clear_undo);
char		*get_path(t_ctx *c);
char		*format_path(t_ctx *c);
bool		file_errors(t_ctx *c, t_error err);
void		gen_prompt(t_ctx *c, const char *path, const char *branch);
void		gen_sad_prompt(t_ctx *c, const char *path);
void		history(t_ctx *c);
void		init_history(t_ctx *c);
char		*get_branch(t_ctx *c);
void		get_weather(t_ctx *c);
t_list		*create_env(t_ctx *c, char **env);
// char		*get_env_by_key(t_list *head, char *key);
// t_env		*get_env_struct_by_key(t_list *head, char *key);
char		**convert_env(t_ctx *c);
t_env		*get_env_by_key(t_list *head, char *key);
t_list		*get_env_list_by_key(t_list *head, char *key);
void		termios_init(t_ctx *c);
void		termios_set(t_ctx *c, short mode);
void		create_error(t_ctx *c, t_error err);

// Signal handlers
void		fork_sig_handler(int sig);
void		sig_handler(int sig);
void		heredoc_sig_handler(int sig);
void		fork_heredoc_sig_handler(int sig);

extern int	g_return;

#endif
