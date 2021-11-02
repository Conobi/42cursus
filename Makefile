SRCS += ./srcs/ft_strlen.c
SRCS += ./srcs/ft_strlcpy.c
SRCS += ./srcs/ft_strlcat.c
SRCS += ./srcs/ft_strncmp.c
SRCS += ./srcs/ft_strdup.c
SRCS += ./srcs/ft_atoi.c
OBJECTS=${SRCS:.c=.o}
CC=gcc
CFLAGS=-I includes -Wall -Wextra -Werror
NAME=libft.a

all: $(NAME)

re: fclean all

$(NAME): $(OBJECTS)
	ar -crs $(NAME) $(OBJECTS)

clean:
	rm -rf $(OBJECTS)

fclean:
	rm -rf $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean fclean re all

