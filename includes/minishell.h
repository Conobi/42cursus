/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:57:41 by abastos           #+#    #+#             */
/*   Updated: 2022/05/23 17:18:36 by abastos          ###   ########lyon.fr   */
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

# define DS_PROMPT	1
// todo: Use ds_prompt settings to enable or disable prompt generation

// GARBAGE TYPE
# define PERM_GB	0
# define PIPE_GB	1
# define CMD_GB		2

// Errors
# define FILE_ERR 	1
# define ERROR		2
# define WARNING	3

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
	t_list				*env;
	char				*weather_emoji;
	int					return_code;
	char				*prompt;
	char				*last_path;
	char				*entry;
	char				*last_entry;
	int					history_fd;
	char				**env_list;
	t_parser			parser;
	struct s_command	*command_table;
	struct termios		term;
	struct termios		base;
}	t_ctx;

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

void	add_command(t_command *command);

// Executor functions
void	exec(t_ctx *c, t_table *table);
void	outfile_handler(t_table *table, int curr_cmd);
void	close_pipes(t_table *table, int pipes);
void	switch_pipes(int in, int out);
void	set_exec_path(t_ctx *c, t_table *table);
void	in_selector(t_table *table, int curr, int *in);
void	out_selector(t_table *table, int curr, int piped_commands, int *out);
char	*find_exec(t_ctx *c, const char *exec_name);
void	create_heredoc(t_ctx *c);

// Builtins
bool	exec_builtin(t_ctx *c);
void	b_cd(t_ctx *c, char *path);
void	b_pwd(t_ctx *c);
void	b_echo(const char *args);
void	b_ls(t_ctx *c, t_table *table, int cmd);
void	rl_replace_line(const char *text, int clear_undo);

// Utils
void	exit_shell(t_ctx *c, int code);
char	*get_path(t_ctx *c);
char	*format_path(t_ctx *c);
bool	error_handler(t_ctx *c, t_error err);
void	gen_prompt(t_ctx *c, const char *path, const char *branch);
void	history(t_ctx *c);
void	init_history(t_ctx *c);
char	*get_branch(t_ctx *c);
void	get_weather(t_ctx *c);
t_list	*create_env(t_ctx *c, char **env);
char	**gb_split(t_ctx *ctx, char const *s, char c);
void	termios_init(t_ctx *c);
void	termios_set(t_ctx *c, short mode);
void	create_error(t_ctx *c, t_error err);

// Signal handlers
void	fork_sig_handler(int sig);
void	sig_handler(int sig);
void	heredoc_sig_handler(int sig);

#endif
