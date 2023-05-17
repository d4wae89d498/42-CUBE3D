#ifndef CUBE3D_H
# define CUBE3D_H

//  INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../srcs/gnl/get_next_line.h"

//  TYPEDEF

typedef enum bool
{
	FALSE = 0,
	TRUE = 1
} e_bool;

typedef enum parse_err
{
	OK,
    WRONG_ARG_NUMBER,
	WRONG_MAP_NAME
} e_parse_err;

//  PROTOTYPE

//		UTILS

int			ft_strlen(char *str);

//      PARSING

e_parse_err	ft_parse(int ac, char **av);
int			ft_parse_error(e_parse_err errtype);
e_bool		ft_is_map_name_valid(char *map_name);

#endif