SRC	=							\
minishell.c						\
executor/executor.c				\
executor/executor_utils.c		\
executor/files_handlers.c		\
shell_subsystems/exit_shell.c	\

NAME		=	minishell
INCS		=	./includes
LIBFT_AR	=	./libft/libft.a

SDIR		=	./src
SRCS		=	$(addprefix ${SDIR}/,${SRC})
ODIR		=	./out
OBJS		=	$(patsubst ${SDIR}/%,${ODIR}/%,${SRCS:.c=.o})

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -I ${INCS}
RM			=	rm -rf

all: libft ${NAME}

libft:
	@make -C ./libft --no-print-directory

${ODIR}/%.o: ${SDIR}/%.c ${INCS}/minishell.h Makefile
	@mkdir -p ${@D}
	${CC} ${CFLAGS} -c $< -o $@ -g3

${NAME}: ${OBJS} ${LIBFT_AR}
	${CC} ${OBJS} ${LIBFT_AR} -lreadline -o ${NAME}

clean:
	make clean -C ./libft
	${RM} ${ODIR}

fclean: clean
	${RM} ${LIBFT_AR}
	${RM} ${NAME}

re: fclean all

.PHONY: all libft clean fclean re
