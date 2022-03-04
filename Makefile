NAME		= philosophers

INC			= philosophers.h
INCDIR		= includes
INCS		= $(addprefix $(INCDIR)/,$(INC))

SRC			= philosophers.c \
			  utils.c \
			  actions.c
SDIR		= srcs
SRCS		= $(addprefix $(SDIR)/,$(SRC))

ODIR		= build
OBJS 		= $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.c=.o))
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g3 -pthread -I $(INCDIR)

all: $(NAME)

$(ODIR)/%.o: $(SDIR)/%.c $(INCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(NAME)


re: fclean all

.PHONY: all clean fclean re
