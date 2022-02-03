NAME		= pipex

LIBFTDIR	= libft
LIBFT_AR	= $(addprefix $(LIBFTDIR)/,libft.a)

INC			= pipex.h
INCDIR		= includes
INCS		= $(addprefix $(INCDIR)/,$(INC))

SRC			= pipex.c \
			  utils.c \
			  memory.c
SDIR		= srcs
SRCS		= $(addprefix $(SDIR)/,$(SRC))

ODIR		= build
OBJS 		= $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.c=.o))
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3 -O3 -I $(INCDIR) -I $(LIBFTDIR)

all: libft $(NAME)

libft:
	make -C $(LIBFTDIR)

$(ODIR)/%.o: $(SDIR)/%.c $(INCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_AR)
	$(CC) $(OBJS) $(LIBFT_AR) -o $(NAME)

clean:
	rm -rf $(ODIR)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -rf $(LIBFT_AR)
	rm -rf $(NAME)


re: fclean all

.PHONY: all libft clean fclean re
