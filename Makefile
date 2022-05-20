BLUE		= \033[0;34m
COMPIL		= \033[3;35m
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0;m

OS			= $(shell uname)

ifeq ($(OS), Darwin)
	RUN_CMD	= script -q $@.log $1 > /dev/null; \
				RESULT=$$?
else ifeq ($(OS), Linux)
	RUN_CMD	= script -q -e -c "$(1)" $@.log > /dev/null; \
				RESULT=$$?; \
				sed -i '1d' $@.log; \
				sed -i "$$(($$(wc -l < $@.log)-1)),\$$d" $@.log
endif

define compile_cmd
	printf "%b%-30b" "$(BLUE)compiling " "$(COMPIL)$(@F)$(RESET)";
	$(RUN_CMD); \
	if [ $$RESULT -ne 0 ]; then \
		printf "%b\n" "$(RED)[✖]$(RESET)"; \
		cat $@.log; \
	else  \
		printf "%b\n" "$(GREEN)[✓]$(RESET)"; \
	fi; \
	rm -f $@.log; \
	exit $$RESULT
endef

NAME		= minishell

LIBFTDIR	= libft
LIBFT_AR	= $(addprefix $(LIBFTDIR)/,libft.a)

RLINCS		= $(shell brew --prefix readline)/include
RLLIB		= $(shell brew --prefix readline)/lib

INC			= minishell.h
INCDIR		= includes
INCS		= $(addprefix $(INCDIR)/,$(INC))

SRC			= minishell.c \
			  executor/executor.c \
			  executor/executor_utils.c \
			  executor/files_handlers.c \
			  executor/heredoc.c \
			  builtins/cd.c \
			  builtins/pwd.c \
			  builtins/echo.c \
			  builtins/ls.c \
	 		  builtins/exit_shell.c \
			  builtins/builtins_manager.c \
			  utils/gb_split.c \
			  utils/prompt_misc.c \
			  utils/managers/path_manager.c \
			  utils/managers/errors_manager.c \
			  utils/managers/history_manager.c \
			  utils/managers/env_manager.c \
			  utils/managers/termios_manager.c \

SDIR		= srcs
SRCS		= $(addprefix $(SDIR)/,$(SRC))

ODIR		= build/$(OS)
OBJS 		= $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.c=.o))
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I $(INCDIR) -I $(LIBFTDIR) -g3

all: libft $(NAME)

libft: check-and-reinit-submodules
	@printf "$(BLUE)compiling $(COMPIL)libft:$(RESET)\n";
	@make -C $(LIBFTDIR) --no-print-directory

$(ODIR)/%.o: $(SDIR)/%.c $(INCS) Makefile
	@mkdir -p $(@D)
	@$(call compile_cmd, $(CC) $(CFLAGS) -c $< -o $@)

$(NAME): $(OBJS) $(LIBFT_AR)
ifndef debug
	@$(call compile_cmd, $(CC) $(OBJS) $(LIBFT_AR) -lreadline -I$(RLINCS) -L$(RLLIB) -o $(NAME))
	@printf "$(GREEN)Done$(RESET)\n";
else
	@$(call compile_cmd, $(CC) $(OBJS) $(LIBFT_AR) -o $(NAME) -lreadline -I$(RLINCS) -L$(RLLIB) -fsanitize=address)
	@printf "$(GREEN)Done debug mode$(RESET)\n";
endif

check-and-reinit-submodules:
	@if git submodule status | egrep -q '^[-]' ; then \
		echo "INFO: Need to reinitialize git submodules"; \
		git submodule update --init --remote; \
	fi

clean:
	@printf "$(RED)Deleting build files$(RESET)\n";
	@rm -rf $(ODIR)
	@printf "$(RED)Clean libft:$(RESET)\n";
	@make clean -C $(LIBFTDIR)

fclean: clean
	@printf "$(RED)Deleting $(LIBFT_AR)$(RESET)\n";
	@rm -rf $(LIBFT_AR)
	@printf "$(RED)Deleting $(NAME)$(RESET)\n";
	@rm -rf $(NAME)

re: fclean all

.PHONY: all libft check-and-reinit-submodules clean fclean re
