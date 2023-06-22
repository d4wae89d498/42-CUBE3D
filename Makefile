#-----------------------------------------------#
#-----------------[ SRCS NAME ]-----------------#
#-----------------------------------------------#

MAIN			= 	srcs/main.c
MAIN_TEST		= 	srcs/main_test.c

SRCS			= 	$(MAIN) \
					srcs/gnl/get_next_line.c srcs/gnl/get_next_line_utils.c \
					srcs/utils/ft_strlen.c srcs/utils/ft_strcmp.c srcs/utils/ft_skip_whitespaces.c srcs/utils/ft_error.c srcs/utils/ft_strtrim_end.c srcs/utils/ft_bzero.c srcs/utils/ft_skip_newlines.c srcs/utils/ft_parse_u1.c \
					srcs/initialization/ft_init.c \
					srcs/parsing/ft_parse.c srcs/parsing/ft_is_map_name_valid.c srcs/parsing/ft_parse_map.c srcs/parsing/ft_parse_textures.c srcs/parsing/ft_parse_colors.c \
					srcs/destruction/ft_destroy.c

#-----------------------------------------------#
#----------------[ COMPILATION ]----------------#
#-----------------------------------------------#

CC				=	gcc
RM				=	rm -rf
CFLAGS			=	# -Wall -Wextra -Werror -O3

HEADERS			=	includes/cube3d.h

NAME			=	cube3D

OBJS			=	$(SRCS:.c=.o)	

#-----------------------------------------------#
#-------------------[ TARGET ]------------------#
#-----------------------------------------------#

all:			$(NAME)

%.o:			%.c $(HEADERS)
				$(CC) $(CFLAGS) -I./includes -I./mlx -c $< -o $@

$(NAME):		$(OBJS)
				make -C mlx
				$(CC) $(CFLAGS) $(OBJS) -Lmlx -lmlx -lXext -lX11 -lm -lz -o $(NAME)

clean:
				make clean -C mlx
				$(RM) $(OBJS)

fclean:			clean
				make fclean -C mlx
				$(RM) $(NAME)

re:				fclean $(NAME)

test:			all clean

.PHONY:			all clean fclean re