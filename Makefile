NAME		= fractol

LIBFTDIR	= libft
LIBFT_AR	= $(addprefix $(LIBFTDIR)/,libft.a)

INC			= fractol.h
INCDIR		= includes
INCS		= $(addprefix $(INCDIR)/,$(INC))

SRC			= fractol.c \
			  handlers.c \
			  utils.c \
			  rgba.c \
			  generators.c \
			  colors.c \
			  events.c
SDIR		= srcs
SRCS		= $(addprefix $(SDIR)/,$(SRC))

ODIR		= build
OBJS 		= $(patsubst $(SDIR)/%,$(ODIR)/%,$(SRCS:.c=.o))

CC			= gcc

OSTEST		:= $(shell uname)

ifeq ($(OSTEST), Darwin)
MLXDIR		= mlx/opengl
MLXFLAGS	= -l mlx -L $(MLXDIR) -framework OpenGL -framework AppKit

CFLAGS		=-Wall -Wextra -Werror -g3 -O3 -I $(INCDIR) -I $(MLXDIR) -I $(LIBFTDIR)
endif

ifeq ($(OSTEST), Linux)
MLXDIR		= mlx/x11
MLXFLAGS	= -l mlx -L $(MLXDIR) -L/usr/lib -I $(MLXDIR) -I/usr/include -lXext -lX11 -lm -lz
CFLAGS		= -Wall -Wextra -Werror -g3 -O3 -I/usr/include -I $(INCDIR) -I $(MLXDIR) -I $(LIBFTDIR)
endif

all: libft mlx $(NAME)

mlx:
	make -C $(MLXDIR)

libft:
	make -C $(LIBFTDIR)

$(ODIR)/%.o: $(SDIR)/%.c $(INCS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_AR)
	$(CC) $(OBJS) $(LIBFT_AR) -o $(NAME) $(MLXFLAGS)

clean:
	rm -rf $(ODIR)
	make clean -C $(LIBFTDIR)
	make clean -C $(MLXDIR)

fclean: clean
	rm -rf $(LIBFT_AR)
	rm -rf $(NAME)


re: fclean all

.PHONY: all libft mlx clean fclean re
