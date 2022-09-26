/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:57:41 by abastos           #+#    #+#             */
/*   Updated: 2022/09/26 19:56:25 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "types.h"

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

// Token definitions for parsing
# define OTHR_TK	0
# define OUT_TK		1
# define IN_TK		2
# define APPD_TK	3
# define HRDC_TK	4

// GARBAGE TYPE
# define PERM_GB		0
# define CMD_GB			1
# define ENTRY_GB		2
# define PIPE_GB		3
# define QUOTE_GB		4
# define REDIR_GB		5
# define HISTR_GB		6
# define CMD1P_GB		7
# define CMD2P_GB		8
# define CMD3P_GB		9
# define CMD4P_GB		10
# define EXPT_PT_GB		11
# define HEREDOCS_GB	12

// Errors
# define FILE_ERR 		1
# define ERROR			2
# define WARNING		3

extern int	g_return;

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

// Executor functions
void		exec(t_ctx *c);
void		close_pipes(t_ctx *c, int pipes);
void		switch_pipes(int in, int out);
char		*find_exec(t_ctx *c, const char *exec_name);
int			set_exec_path(t_ctx *c, t_ncommand *cmd);
int			open_heredocs(t_ctx *c);
int			create_heredoc(t_ctx *c, const char *stop);
char		*heredoc_env_replace(t_ctx *c, const char *str);
void		child_status(int status);
void		exec_fork(t_ctx *c, int curr, int *in, int *out);

// Builtins
bool		is_builtin(t_ncommand cmd);
int			exec_builtin(t_ctx *c, t_ncommand cmd);
int			b_cd(t_ctx *c, char *path);
int			b_pwd(t_ctx *c);
int			b_echo(t_ncommand cmd);
int			b_ls(t_ctx *c, int cmd);
int			b_exit(t_ctx *c, t_ncommand cmd);
void		exit_shell(t_ctx *c, int code, int no_print);
int			b_export(t_ctx *c, int argc, char **argv);
void		set_list_entry(t_ctx *c, char *key,
				char *value, bool unset);
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
t_list		*create_env_entry(t_ctx *c, char *entry);
char		**convert_env(t_ctx *c);
t_env		*get_env_by_key(t_list *head, char *key);
t_list		*get_env_list_by_key(t_list *head, char *key);
void		termios_init(t_ctx *c);
void		termios_set(t_ctx *c, short mode);
void		create_error(t_ctx *c, t_error err);

// File handlers
bool		io_handler(t_ctx *c, int curr, int *in, int *out);
bool		outfile_handler(t_ctx *c, int curr_cmd);
bool		infile_handler(t_ctx *c, int curr_cmd);
void		in_selector(t_ctx *c, int curr, int *in);
void		out_selector(t_ctx *c, int curr, int *out);

// Signal handlers
void		fork_sig_handler(int sig);
void		sig_handler(int sig);
void		heredoc_sig_handler(int sig);
void		fork_heredoc_sig_handler(int sig);

// Safe memory handler
void		*sf_add(void *ptr, t_garbc **garbcl, const short type);
void		*sf_calloc(size_t count, size_t size,
				const short type, t_garbc **last);
void		enomem_error(t_garbc **garbcl);

// Fd garbage collector
t_fdgbc		*fdgb_init(void);
int			fdgb_add(int fd, t_fdgbc **fdgbcl, const short type);
void		fdgb_close_all(t_fdgbc **fdgbcl);
void		fdgb_close(t_fdgbc **fdgbcl, const short type);

#endif
