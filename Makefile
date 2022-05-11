NAME		= minishell

LIBFTDIR	= libft
LIBFT_AR	= $(addprefix $(LIBFTDIR)/,libft.a)

INC			= minishell.h
INCDIR		= includes
INCS		= $(addprefix $(INCDIR)/,$(INC))

SRC			= minishell.c \
			  executor/executor.c \
			  executor/executor_utils.c \
			  executor/files_handlers.c \
	 		  parsing/parser.c \
	 		  parsing/pipe.c \
	 		  utils/exit_shell.c \

SDIR		= srcs
SRCS		= $(addprefix $(SDIR)/,$(SRC))

ODIR		= build
OBJS 		= $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.c=.o))
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I $(INCDIR) -I $(LIBFTDIR) -g3

all: libft $(NAME)

libft: check-and-reinit-submodules
	make -C $(LIBFTDIR)

$(ODIR)/%.o: $(SDIR)/%.c $(INCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_AR)
	$(CC) $(OBJS) $(LIBFT_AR) -o $(NAME) -lreadline -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include

check-and-reinit-submodules:
	@if git submodule status | egrep -q '^[-]' ; then \
		echo "INFO: Need to reinitialize git submodules"; \
		git submodule update --init --remote; \
	fi

clean:
	rm -rf $(ODIR)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -rf $(LIBFT_AR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all libft check-and-reinit-submodules clean fclean re
