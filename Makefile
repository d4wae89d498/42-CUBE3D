#-----------------------------------------------#
#-----------------[ SRCS NAME ]-----------------#
#-----------------------------------------------#

SRCS		=		srcs/main.c \
					srcs/gnl/get_next_line.c srcs/gnl/get_next_line_utils.c \
					srcs/utils/ft_strlen.c \
					srcs/parsing/ft_parse.c srcs/parsing/ft_parse_error.c srcs/parsing/ft_is_map_name_valid.c

#-----------------------------------------------#
#----------------[ COMPILATION ]----------------#
#-----------------------------------------------#

CC				=	gcc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror

HEADERS			=	includes/cube3d.h

NAME			=	cube3D

OBJS			=	$(SRCS:.c=.o)	

#-----------------------------------------------#
#-------------------[ TARGET ]------------------#
#-----------------------------------------------#

all:			$(NAME)

%.o:			%.c $(HEADERS)
				$(CC) $(CFLAGS) -I./includes -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

test:			all clean

.PHONY:			all clean fclean re