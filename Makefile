NAME		= philo

INC			= philosophers.h
INCDIR		= includes
INCS		= $(addprefix $(INCDIR)/,$(INC))

SRC			= philosophers.c \
			  init.c \
			  utils.c \
			  death.c
SDIR		= srcs
SRCS		= $(addprefix $(SDIR)/,$(SRC))

ODIR		= build
OBJS 		= $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.c=.o))
CC			= gcc
# CFLAGS		= -Wall -Wextra -Werror -pthread -g3 -I $(INCDIR)
CFLAGS		= -Wall -Wextra -Werror -fsanitize=thread -g -pthread -I $(INCDIR)

all: $(NAME)

$(ODIR)/%.o: $(SDIR)/%.c $(INCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(NAME)


re: fclean all

.PHONY: all clean fclean re
