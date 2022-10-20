BLUE		= \033[0;34m
COMPIL		= \033[3;35m
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

NAME		= cub3d

LIBFTDIR	= libft
LIBFT_AR	= $(addprefix $(LIBFTDIR)/,libft.a)

ifeq ($(OS), Darwin)
MLXDIR		= mlx/opengl
else ifeq ($(OS), Linux)
MLXDIR		= mlx/x11
endif

MLX_AR		= $(MLXDIR)/libmlx.a

INC			= cub3d.h \
			  events.h \
			  keys.h \
			  types.h
INCDIR		= includes
INCS		= $(addprefix $(INCDIR)/,$(INC))

SRC			= main.c \
			  initialize.c \
			  handlers.c \
			  events_handlers.c \
			  move_handler.c \
			  engine/generator.c \
			  engine/rays.c \
			  engine/rays_utils.c \
			  engine/render.c \
			  minimap/draw_map.c \
			  minimap/draw_map_utils.c \
			  utils/draw.c \
			  utils/utils.c \
			  utils/helpers.c \
			  utils/colors.c \
			  parsing/checkers.c \
			  parsing/utils.c \
			  parsing/color_parser.c \
			  parsing/texture_parser.c \
			  parsing/map_parser.c \
			  parsing/map_parser_utils.c \
			  parsing/unsplitable.c

SDIR		= srcs
SRCS		= $(addprefix $(SDIR)/,$(SRC))

ODIR		= build/$(OS)
OBJS 		= $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.c=.o))
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -I $(MLXDIR) -I $(INCDIR) -I $(LIBFTDIR) -std=c99 -O2

all: mlx libft $(NAME)

check-and-reinit-submodules:
	@if git submodule status | egrep -q '^[-]' ; then \
			echo "INFO: Need to reinitialize git submodules"; \
			git submodule update --init --remote; \
	fi

libft: check-and-reinit-submodules
	@printf "$(BLUE)compiling $(COMPIL)libft:$(RESET)\n";
	@make -C $(LIBFTDIR) --no-print-directory

mlx: check-and-reinit-submodules
	@printf "$(BLUE)compiling $(COMPIL)mlx:$(RESET)\n";
	@make -C $(MLXDIR) --no-print-directory

$(ODIR)/%.o: $(SDIR)/%.c $(INCS) Makefile
	@mkdir -p $(@D)
	@$(call compile_cmd, $(CC) $(CFLAGS) -c $< -o $@)

$(NAME): $(OBJS) $(LIBFT_AR) $(MLX_AR)
ifeq ($(OS), Darwin)
	@$(call compile_cmd, $(CC) $(OBJS) $(LIBFT_AR) $(MLX_AR) -g -l mlx -L $(MLXDIR) -framework OpenGL -framework AppKit -o $(NAME))
else ifeq ($(OS), Linux)
	@$(call compile_cmd, $(CC) $(OBJS) $(LIBFT_AR) $(MLX_AR) -l mlx -L $(MLXDIR) -L/usr/lib -I $(MLXDIR) -I/usr/include -lXext -lX11 -lm -lz -o $(NAME))
endif
	@printf "$(GREEN)Done$(RESET)\n";

debug: $(OBJS) $(LIBFT_AR)
ifeq ($(OS), Darwin)
	@$(call compile_cmd, $(CC) $(OBJS) $(LIBFT_AR) $(MLX_AR) -g -l mlx -L $(MLXDIR) -framework OpenGL -framework AppKit -o $(NAME) -fsanitize=address)
else ifeq ($(OS), Linux)
	@$(call compile_cmd, $(CC) $(OBJS) $(LIBFT_AR)  $(MLX_AR) -l mlx -L $(MLXDIR) -L/usr/lib -I $(MLXDIR) -I/usr/include -lXext -lX11 -lm -lz -fsanitize=address)
endif
	@printf "$(GREEN)Done debug mode$(RESET)\n";

clean: check-and-reinit-submodules
	@printf "$(RED)Deleting build files$(RESET)\n";
	@rm -rf $(ODIR)
	@printf "$(RED)Clean libft:$(RESET)\n";
	@make clean -C $(LIBFTDIR)

fclean: clean
	@printf "$(RED)Deleting $(LIBFT_AR)$(RESET)\n";
	@rm -rf $(LIBFT_AR)
	@printf "$(RED)Deleting $(MLX_AR)$(RESET)\n";
	@rm -rf $(MLX_AR)
	@printf "$(RED)Deleting $(NAME)$(RESET)\n";
	@rm -rf $(NAME)

re: fclean all

.PHONY: all libft mlx clean fclean re
