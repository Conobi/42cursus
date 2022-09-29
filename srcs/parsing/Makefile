NAME = parser

LIBFT_AR =	../../libft/libft.a \

INC		=	parser.h
INCDIR	=	.
INCS	=	$(addprefix $(INCDIR)/,$(INC))

SRC		=	parser.c \
			char_split.c \
			checkers.c \
			utils.c
SDIR	=	.
SRCS	=	$(addprefix $(SDIR)/,$(SRC))

ODIR	= build
OBJS 	= $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.c=.o))

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 -I ../parser -I ../../libft

all : libft $(NAME)

libft:
	make -C ../../libft

$(ODIR)/%.o: $(SDIR)/%.c $(INCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_AR)
	$(CC) $(OBJS) $(LIBFT_AR) -o $(NAME)

clean:
	rm -rf $(ODIR)
	make clean -C ../../libft

fclean: clean
	rm -rf $(LIBFT_AR)
	rm -rf $(NAME)


re: fclean all

.PHONY: all libft clean fclean re
