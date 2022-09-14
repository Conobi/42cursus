/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:18:18 by abastos           #+#    #+#             */
/*   Updated: 2022/09/14 18:39:30 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "libs.h"

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
	bool	is_builtins;
}	t_ncommand;

typedef struct s_parser {
	bool	squoted;
	bool	dquoted;
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

#endif
