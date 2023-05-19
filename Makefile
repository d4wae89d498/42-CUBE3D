#-----------------------------------------------#
#-----------------[ SRCS NAME ]-----------------#
#-----------------------------------------------#

SRCS		=		srcs/main.c \
					srcs/gnl/get_next_line.c srcs/gnl/get_next_line_utils.c \
					srcs/utils/ft_strlen.c srcs/utils/ft_strcmp.c srcs/utils/ft_skip_whitespaces.c srcs/utils/ft_error.c srcs/utils/ft_strtrim_end.c \
					srcs/initialization/ft_init.c \
					srcs/parsing/ft_parse.c srcs/parsing/ft_is_map_name_valid.c srcs/parsing/ft_parse_map.c srcs/parsing/ft_parse_textures.c

#-----------------------------------------------#
#----------------[ COMPILATION ]----------------#
#-----------------------------------------------#

CC				=	gcc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -O3

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
				$(CC) $(CFLAGS) $(OBJS) -Lmlx -lmlx -lXext -lX11 -lm -lz -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

test:			all clean

.PHONY:			all clean fclean re