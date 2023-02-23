BLUE		= \033[0;34m
COMPIL	= \033[3;35m
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0;m

OS			= $(shell uname)

ifeq ($(OS), Darwin)
	RUN_CMD	= script -q $@.log $1 > /dev/null; \
	RESULT=$$?
else ifeq ($(OS), Linux)
	RUN_CMD	= script -q -e -c "$(1)" $@.log > /dev/null; \
	RESULT=$$?; \
	sed -i '1d' $@.log; \
	sed -i "$$(($$(wc -l < $@.log)-1)),\$$d" $@.log
endif

define compile_cmd
	printf "%b%-30b" "$(BLUE)compiling " "$(COMPIL)$(@F)$(RESET)";
	$(RUN_CMD); \
	if [ $$RESULT -ne 0 ]; then \
		printf "%b\n" "$(RED)[✖]$(RESET)"; \
		cat $@.log; \
	else  \
		printf "%b\n" "$(GREEN)[✓]$(RESET)"; \
	fi; \
	rm -f $@.log; \
	exit $$RESULT
endef

NAME		= ircserv

INC			= irc.hpp \
			  Server.hpp \
			  Socket.hpp \
			  Logger.hpp

INCDIR		= includes
INCS		= $(addprefix $(INCDIR)/,$(INC))

SRC			= main.cpp \
			  server/Server.cpp \
			  server/Server_utils.cpp \
			  socket/Socket.cpp \
			  client/Client.cpp \
			  logger/Logger.cpp

SDIR		= srcs
SRCS		= $(addprefix $(SDIR)/,$(SRC))

ODIR		= build/$(OS)
OBJS 		= $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.cpp=.o))
CC			= c++
CFLAGS		= -Wall -Wextra -Werror -I $(INCDIR) -std=c++98 -O1 -g3

all: $(NAME)

$(ODIR)/%.o: $(SDIR)/%.cpp $(INCS) Makefile
	@mkdir -p $(@D)
	@$(call compile_cmd, $(CC) $(CFLAGS) -c $< -o $@)

$(NAME): $(OBJS)
	@$(call compile_cmd, $(CC) $(CFLAGS) $(OBJS) -o $(NAME))
	@printf "$(GREEN)Done$(RESET)\n";

debug: $(OBJS)
	@$(call compile_cmd, $(CC) $(CFLAGS) $(OBJS) -o $(NAME) -fsanitize=address)
	@printf "$(GREEN)Done debug mode$(RESET)\n";

clean:
	@printf "$(RED)Deleting build files$(RESET)\n";
	@rm -rf $(ODIR)

fclean: clean
	@printf "$(RED)Deleting $(NAME)$(RESET)\n";
	@rm -rf $(NAME)

re: fclean all

.PHONY: all libft clean fclean re
