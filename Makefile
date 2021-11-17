SRC = \
write_utils.c \
printer_utils.c \
ft_printf.c
CC=gcc
SDIR=srcs
SRCS=$(addprefix $(SDIR)/,$(SRC))
OBJS=${SRCS:.c=.o}
CFLAGS=-Wall -Wextra -Werror -I $(HDRS)
NAME=libftprintf.a
LIB=libft
HDRS=includes

all: $(NAME)

re: fclean all

$(NAME): $(OBJS)
	make -C $(LIB)
	cp libft/libft.a $(NAME)
	ar -rcs $(NAME) $(OBJS)

clean:
	make -C $(LIB) clean
	rm -rf $(OBJS)

fclean:
	make -C $(LIB) fclean
	rm -rf $(NAME) $(OBJS)

$(SDIR)/%.o: $(SDIR)/%.c $(HDRS)/ft_printf.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all re clean fclean
