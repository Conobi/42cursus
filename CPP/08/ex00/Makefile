NAME		= exec

INC			= easyfind.hpp
INCDIR		= .
INCS		= $(addprefix $(INCDIR)/,$(INC))


SRC			= main.cpp
SDIR		= .
SRCS		= $(addprefix $(SDIR)/,$(SRC))

ODIR		= build
OBJS 		= $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.cpp=.o))
CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98 -I $(INCDIR)

all: $(NAME)

$(ODIR)/%.o: $(SDIR)/%.cpp $(INCS) Makefile
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
