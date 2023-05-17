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

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_parse_err
{
	OK,
    WRONG_ARG_NUMBER,
	WRONG_MAP_NAME,
	OPEN_ERROR,
	MAP_ERROR
}	t_parse_err;

typedef enum e_direction
{
	NO,
	SO,
	EA,
	WE,
	NOT_VALID
}	t_direction;

typedef struct s_texture
{
	t_direction direction;
	char		*texture;
}	t_texture;

typedef	struct s_map
{
	char		**map_data;
	t_texture	textures[4];
}	t_map;

//  PROTOTYPE

//		UTILS

int			ft_strlen(char *str);
t_bool		ft_strcmp(char *s1, char *s2);
void	    ft_skip_whitespaces(char **str);

//      PARSING

t_parse_err	ft_parse(int ac, char **av, t_map *map);
int			ft_parse_error(t_parse_err errtype);
t_bool		ft_is_map_name_valid(char *map_name);
t_bool		ft_parse_map(int fd, t_map *map);

#endif