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
./srcs/ft_memmove.c \
./srcs/ft_strnstr.c \
./srcs/ft_calloc.c \
./srcs/ft_substr.c \
./srcs/ft_strtrim.c \
./srcs/ft_putchar_fd.c \
./srcs/ft_putstr_fd.c \
./srcs/ft_putendl_fd.c \
./srcs/ft_putnbr_fd.c \
./srcs/ft_strmapi.c \
./srcs/ft_striteri.c
SRCS_BONUS= \
./srcs/ft_lstnew.c \
./srcs/ft_lstadd_front.c \
./srcs/ft_lstsize.c \
./srcs/ft_lstlast.c \
./srcs/ft_lstadd_back.c \
./srcs/ft_lstdelone.c \
./srcs/ft_lstiter.c \
./srcs/ft_lstclear.c \
./srcs/ft_lstmap.c
OBJECTS=${SRCS:.c=.o}
OBJECTS_BONUS=${SRCS:.c=.o} ${SRCS_BONUS:.c=.o}
CC=gcc
CFLAGS=-I includes -Wall -Wextra -Werror
NAME=libft.a

all: $(NAME)

re: fclean all

$(NAME): $(OBJECTS)
	ar -crs $(NAME) $(OBJECTS)

bonus: $(OBJECTS_BONUS)
	ar -crs $(NAME) $(OBJECTS_BONUS)

clean:
	rm -rf $(OBJECTS)

bclean:
	rm -rf $(OBJECTS_BONUS)

fclean:
	rm -rf $(NAME) $(OBJECTS)

%.o: %.c $(HDRS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean fclean rclean bclean re all bonus

