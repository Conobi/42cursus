NAME	= fractol

LIBFTDIR=	libft
LIBFT_AR=	$(addprefix $(LIBFTDIR)/,libft.a)

INC		=	fractol.h
INCDIR	=	includes
INCS	=	$(addprefix $(INCDIR)/,$(INC))

SRC		=	fractol.c \
			handlers.c
SDIR	=	srcs
SRCS	=	$(addprefix $(SDIR)/,$(SRC))

OBJS 	= $(SRCS:.c=.o)

MLXDIR	=	mlx
MLXFLAGS=	-L$(MLXDIR) -l$(MLXDIR) -framework OpenGL -framework AppKit

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3 -I $(INCDIR) -I $(MLXDIR) -I $(LIBFTDIR)

all : libft mlx $(NAME)

mlx:
	make -C $(MLXDIR)

libft:
	make -C $(LIBFTDIR)

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_AR)
	$(CC) $(MLXFLAGS) $(OBJS) $(LIBFT_AR) -o $(NAME)

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFTDIR)
	make clean -C $(MLXDIR)

fclean: clean
	rm -rf $(LIBFT_AR)
	rm -rf $(NAME)


re: fclean all

.PHONY: all libft mlx clean fclean re
