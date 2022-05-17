NAME		= libft.a

INC			= libft.h
INCDIR		= .
INCS		= $(addprefix $(INCDIR)/,$(INC))

SRC = ft_strlen.c \
	  ft_strlcpy.c \
	  ft_strlcat.c \
	  ft_strncmp.c \
	  ft_strdup.c \
	  ft_atoi.c \
	  ft_split.c \
	  ft_strjoin.c \
	  ft_itoa.c \
	  ft_isalpha.c \
	  ft_isdigit.c \
	  ft_isalnum.c \
	  ft_isascii.c \
	  ft_isprint.c \
	  ft_toupper.c \
	  ft_tolower.c \
	  ft_strchr.c \
	  ft_strrchr.c \
	  ft_memchr.c \
	  ft_memcmp.c \
	  ft_memset.c \
	  ft_bzero.c \
	  ft_memcpy.c \
	  ft_memmove.c \
	  ft_strnstr.c \
	  ft_calloc.c \
	  ft_substr.c \
	  ft_strtrim.c \
	  ft_putchar_fd.c \
	  ft_putstr_fd.c \
	  ft_putendl_fd.c \
	  ft_putnbr_fd.c \
	  ft_strmapi.c \
	  ft_striteri.c \
	  ft_lstnew.c \
	  ft_lstadd_front.c \
	  ft_lstsize.c \
	  ft_lstlast.c \
	  ft_lstadd_back.c \
	  ft_lstdelone.c \
	  ft_lstiter.c \
	  ft_lstclear.c \
	  ft_lstmap.c \
	  ft_aconcat.c \
	  gb_init.c \
	  gb_calloc.c \
	  gb_delete.c \
	  gb_clear.c \
	  gb_add.c \
	  ft_gnl.c \
	  ft_gnl_utils.c
SDIR		= .
SRCS		= $(addprefix $(SDIR)/,$(SRC))

ODIR		= build
OBJS 		= $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.c=.o))
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I $(INCDIR)

all: $(NAME)

bonus: all

$(ODIR)/%.o: $(SDIR)/%.c $(INCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_AR)
	ar -crs $(NAME) $(OBJS)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
