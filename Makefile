NAME = push_swap

LIBFT_AR =	./libft/libft.a \

INC		=	push_swap.h
INCDIR	=	includes
INCS	=	$(addprefix $(INCDIR)/,$(INC))

SRC		=	push_swap.c \
			push_swap_utils.c \
			operations.c \
			parser.c \
			indexer.c
SDIR	=	srcs
SRCS	=	$(addprefix $(SDIR)/,$(SRC))

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -I $(INCDIR)

all : libft $(NAME)

libft:
	make -C ./libft

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_AR)
	$(CC) $(OBJS) $(LIBFT_AR) -o $(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C ./libft

fclean: clean
	rm -rf $(LIBFT_AR)
	rm -rf $(NAME)


re: fclean all

.PHONY: all libft clean fclean re
