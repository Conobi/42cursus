/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:57:41 by abastos           #+#    #+#             */
/*   Updated: 2022/06/08 17:16:50 by conobi           ###   ########lyon.fr   */
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
// Linux required
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

# define PDEBUG	1

//Term colors
# define RED_FG	"\e[91m"
# define GRN_FG	"\e[32m"
# define YEL_FG	"\e[33m"
# define BLU_FG	"\e[34m"
# define MAG_FG	"\e[35m"
# define CYN_FG	"\e[36m"
# define WHT_FG	"\e[37m"
# define BLK_FG	"\e[30m"

# define RED_BG	"\e[101m"
# define GRN_BG	"\e[42m"
# define YEL_BG	"\e[43m"
# define BLU_BG	"\e[44m"
# define MAG_BG	"\e[45m"
# define CYN_BG	"\e[46m"
# define WHT_BG	"\e[47m"
# define BLK_BG	"\e[40m"
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

typedef struct s_redir {
	char	*arg;
	short	type;
}	t_redir;

typedef struct s_ncommand {
	int		argc;
	char	**argv;
	int		redc;
	t_redir	*redirections;
}	t_ncommand;

typedef struct s_parser {
	char	squoted;
	char	dquoted;
	char	**pipes;
	char	***split;
	int		pipes_n;
	int		len;
}	t_parser;

typedef struct s_ctx {
	t_garbc				*gbc;
	char				*prompt;
	char				*entry;
	t_parser			parser;
	struct s_command	*command_table;
	struct s_ncommand	*cmds;
}	t_ctx;

typedef struct s_table {
	int					commands_num;
	struct s_command	*command_table;
	pid_t				*process;
	int					cmd_idx;
	int					*pipe_fd;
}	t_table;

void		add_args(char *arg);
void		add_command(t_command *command);

// Execu	tor functions
void		exec(t_table *table);
char		*find_exec(char *exec_name);
void		outfile_handler(t_table *table, int curr_cmd);
void		close_pipes(t_table *table, int pipes);
void		switch_pipes(int in, int out);
void		set_exec_path(t_table *table);
void		in_selector(t_table *table, int curr, int *in);
void		out_selector(t_table *table,
				int curr, int piped_commands, int *out);

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

#endif
