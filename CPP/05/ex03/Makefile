NAME		= intern

INC			= Bureaucrat.hpp \
			  AForm.hpp \
			  PresidentialPardonForm.hpp \
			  ShrubberyCreationForm.hpp \
			  RobotomyRequestForm.hpp \
			  Intern.hpp
INCDIR		= .
INCS		= $(addprefix $(INCDIR)/,$(INC))


SRC			= main.cpp \
			  Bureaucrat.cpp \
			  AForm.cpp \
			  PresidentialPardonForm.cpp \
			  ShrubberyCreationForm.cpp \
			  RobotomyRequestForm.cpp \
			  Intern.cpp
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
