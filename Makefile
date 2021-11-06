SRCS = \
./srcs/ft_strlen.c \
./srcs/ft_strlcpy.c \
./srcs/ft_strlcat.c \
./srcs/ft_strncmp.c \
./srcs/ft_strdup.c \
./srcs/ft_atoi.c \
./srcs/ft_split.c \
./srcs/ft_strjoin.c \
./srcs/ft_itoa.c \
./srcs/ft_isalpha.c \
./srcs/ft_isdigit.c \
./srcs/ft_isalnum.c \
./srcs/ft_isascii.c \
./srcs/ft_isprint.c \
./srcs/ft_toupper.c \
./srcs/ft_tolower.c \
./srcs/ft_strchr.c \
./srcs/ft_strrchr.c \
./srcs/ft_memchr.c \
./srcs/ft_memcmp.c \
./srcs/ft_memset.c \
./srcs/ft_bzero.c \
./srcs/ft_memcpy.c \
./srcs/ft_memmove.c
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

.PHONY: clean fclean rclean re all

