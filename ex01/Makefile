NAME		= brain

INC			= main.hpp \
			  Animal.hpp \
			  Cat.hpp \
			  Dog.hpp \
			  WrongAnimal.hpp \
			  WrongCat.hpp \
			  Brain.hpp
INCDIR		= includes
INCS		= $(addprefix $(INCDIR)/,$(INC))


SRC			= main.cpp \
			  Animal.cpp \
			  Cat.cpp \
			  Dog.cpp \
			  Brain.cpp
SDIR		= srcs
SRCS		= $(addprefix $(SDIR)/,$(SRC))

ODIR		= build
OBJS 		= $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.cpp=.o))
CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98 -g3 -I $(INCDIR)

all: $(NAME)

$(ODIR)/%.o: $(SRCS) $(INCS) Makefile
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
