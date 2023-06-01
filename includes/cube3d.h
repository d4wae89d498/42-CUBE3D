#ifndef CUBE3D_H
# define CUBE3D_H

//  INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mlx.h>

#include "../srcs/gnl/get_next_line.h"

//	DEFINE

#define TEXTURE_WIDTH 50
#define TEXTURE_HEIGHT 50

//  TYPEDEF

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_err
{
	OK,
	INITIALIZATION_ERROR,
    WRONG_ARG_NUMBER,
	WRONG_MAP_NAME,
	OPEN_ERROR,
	MAP_ERROR
}	t_err;

typedef enum e_direction
{	
	NONE = 0,
	NO,
	SO,
	EA,
	WE
}	t_direction;

typedef struct s_texture
{
	t_direction direction;
	void		*texture_img;
	int			width;
	int			height;
}	t_texture;

typedef	struct s_map
{
	char		**map_data;
}	t_map;

typedef struct s_data
{
	t_map		map;
	t_texture	textures[4];
	void		*mlx;
}	t_data;

//  PROTOTYPE

//		UTILS

int			ft_strlen(char *str);
t_bool		ft_strcmp(char *s1, char *s2);
size_t	    ft_skip_whitespaces(char *str);
int			ft_error(t_err errtype, t_data *data);
void 		ft_strtrim_end(char *str);
void    	ft_bzero(void *data, size_t n);
t_bool		ft_skip_newlines(int fd, char **current_line);

//		INITIALIZATION

t_err		ft_init(t_data *data);

//      PARSING

t_err		ft_parse(int ac, char **av, t_data *data);
t_bool		ft_is_map_name_valid(char *map_name);
t_bool		ft_parse_map(int fd, t_data *data);
t_bool		ft_parse_textures(int fd, t_data *data);
t_bool		ft_parse_colors(int fd, char *line);

//		DESTRUCTION

void    	ft_destroy(t_data *data);

#endif