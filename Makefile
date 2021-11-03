SRCS += ./srcs/ft_strlen.c
SRCS += ./srcs/ft_strlcpy.c
SRCS += ./srcs/ft_strlcat.c
SRCS += ./srcs/ft_strncmp.c
SRCS += ./srcs/ft_strdup.c
SRCS += ./srcs/ft_atoi.c
SRCS += ./srcs/ft_split.c
SRCS += ./srcs/ft_strjoin.c
SRCS += ./srcs/ft_itoa.c
SRCS += ./srcs/ft_isalpha.c
SRCS += ./srcs/ft_isdigit.c
SRCS += ./srcs/ft_isalnum.c
SRCS += ./srcs/ft_isascii.c
SRCS += ./srcs/ft_isprint.c
SRCS += ./srcs/ft_toupper.c
SRCS += ./srcs/ft_tolower.c
OBJECTS=${SRCS:.c=.o}
CC=gcc
CFLAGS=-I includes -Wall -Wextra -Werror
NAME=libft.a

all: $(NAME)

re: fclean all

rclean: all clean

$(NAME): $(OBJECTS)
	ar -crs $(NAME) $(OBJECTS)

clean:
	rm -rf $(OBJECTS)

fclean:
	rm -rf $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean fclean rclean re all

