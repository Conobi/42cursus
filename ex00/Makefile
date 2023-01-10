NAME		= polymorphism

INC			= main.hpp \
			  Animal.hpp \
			  Cat.hpp \
			  Dog.hpp \
			  WrongAnimal.hpp \
			  WrongCat.hpp
INCDIR		= includes
INCS		= $(addprefix $(INCDIR)/,$(INC))


SRC			= main.cpp \
			  Animal.cpp \
			  Cat.cpp \
			  Dog.cpp \
			  WrongAnimal.cpp \
			  WrongCat.cpp
SDIR		= srcs
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
