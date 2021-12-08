SRC = \
custom_libft.c \
ft_printf_utils.c \
ft_printf.c
CC=gcc
SDIR=srcs
SRCS=$(addprefix $(SDIR)/,$(SRC))
OBJS=${SRCS:.c=.o}
CFLAGS=-Wall -Wextra -Werror -I $(HDRS)
NAME=libftprintf.a
HDRS=includes

all: $(NAME)

re: fclean all

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

bonus: all

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(NAME) $(OBJS)

$(SDIR)/%.o: $(SDIR)/%.c $(HDRS)/ft_printf.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all re bonus clean fclean
