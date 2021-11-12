SRCS = \
./ft_strlen.c \
./ft_strlcpy.c \
./ft_strlcat.c \
./ft_strncmp.c \
./ft_strdup.c \
./ft_atoi.c \
./ft_split.c \
./ft_strjoin.c \
./ft_itoa.c \
./ft_isalpha.c \
./ft_isdigit.c \
./ft_isalnum.c \
./ft_isascii.c \
./ft_isprint.c \
./ft_toupper.c \
./ft_tolower.c \
./ft_strchr.c \
./ft_strrchr.c \
./ft_memchr.c \
./ft_memcmp.c \
./ft_memset.c \
./ft_bzero.c \
./ft_memcpy.c \
./ft_memmove.c \
./ft_strnstr.c \
./ft_calloc.c \
./ft_substr.c \
./ft_strtrim.c \
./ft_putchar_fd.c \
./ft_putstr_fd.c \
./ft_putendl_fd.c \
./ft_putnbr_fd.c \
./ft_strmapi.c \
./ft_striteri.c
SRCS_BONUS= \
./ft_lstnew.c \
./ft_lstadd_front.c \
./ft_lstsize.c \
./ft_lstlast.c \
./ft_lstadd_back.c \
./ft_lstdelone.c \
./ft_lstiter.c \
./ft_lstclear.c \
./ft_lstmap.c
OBJECTS=${SRCS:.c=.o}
OBJECTS_BONUS=${SRCS_BONUS:.c=.o}
CC=gcc
CFLAGS=-Wall -Wextra -Werror -I $(HDRS)
NAME=libft.a
HDRS=libft.h

all: $(NAME)

re: fclean all

$(NAME): $(OBJECTS)
	ar -crs $(NAME) $(OBJECTS)

bonus: $(OBJECTS) $(OBJECTS_BONUS)
	ar -crs $(NAME) $(OBJECTS) $(OBJECTS_BONUS)

clean:
	rm -rf $(OBJECTS) $(OBJECTS_BONUS)

fclean:
	rm -rf $(NAME) $(OBJECTS)

%.o: %.c $(HDRS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean fclean rclean re all bonus

