#ifndef CUBE3D_H
# define CUBE3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "../srcs/gnl/get_next_line.h"
# define MAX_MAP_WIDTH 40
# define MAX_MAP_HEIGHT 40
# define WIDTH 800
# define HEIGHT 600
# define PI 3.14159265359
// (60 * (PI / 180))
# define FOV_ANGLE 1.0471975511965979
# define DEFAULT_TEXTURE "assets/wall.xpm"
# define DEFAULT_SKY_COLOR 255
# define DEFAULT_FLOOR_COLOR 16711680
# define MOVE_SPEED 0.10
# define ROT_SPEED 0.10
//  TYPEDEF

typedef unsigned char	t_u1;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_side
{
	NO_SIDE,
	F = 1,
	C = 2
}	t_side;

typedef enum e_err
{
	OK,
	INITIALIZATION_ERROR,
	WRONG_ARG_NUMBER,
	WRONG_MAP_NAME,
	OPEN_ERROR,
	MAP_ERROR,
	MATCH
}	t_err;

typedef enum e_direction
{
	NONE,
	NORTH,
	SOUTH,
	EAST,
	WEST,
}	t_direction;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_mlx_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_mlx_img;

typedef struct s_parser
{
	int		texture_index;
	char	*line;
	int		nonempty;
	int		col;
	int		row;
	int		found_pos;
	int		fd;
}	t_parser;

typedef struct s_game_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_player		player;
	t_mlx_img		img;
	t_bool			textures_state[4];
	t_bool			floor_set;
	t_bool			sky_set;
	t_mlx_img		textures[4];
	t_mlx_img		default_texture;
	unsigned int	floor_color;
	unsigned int	sky_color;
	char			map[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
	t_parser		parser;
}	t_game_data;

//  PROTOTYPE

//		UTILS

int				ft_strlen(char *str);
t_bool			ft_strcmp(char *s1, char *s2);
size_t			ft_skip_whitespaces(char *str);
int				ft_error(t_err errtype, t_game_data *data);
void			ft_strtrim_end(char *str);
void			ft_bzero(void *data, size_t n);
t_bool			ft_skip_newlines(int fd, char **current_line);
t_bool			ft_parse_u1(char *number, t_u1 *out);

//		INITIALIZATION

t_err			ft_init(t_game_data *data);

//      PARSING

t_err			ft_parse(int ac, char **av, t_game_data *data);
t_bool			ft_is_map_name_valid(char *map_name);
t_bool			ft_parse_map(int fd, t_game_data *data);
t_err			ft_parse_textures(int fd, t_game_data *data, char *line);
t_err			ft_parse_colors(int fd, t_game_data *data, char *line);
t_err			ft_parse_map_cells(int fd, t_game_data *data, char *line);
t_bool			is_valid_map(char map[MAX_MAP_HEIGHT][MAX_MAP_WIDTH]);
void			init_base_position(t_game_data *data, char c, int col, int row);
//		DESTRUCTION

void			ft_destroy(t_game_data *data);
int				ft_sfr(void *data, int ret);

// EVENT

int				key_press(int keycode, void *param);

// GFX

void			raycasting(t_game_data *data );
void			ft_mlx_pixel(t_mlx_img img, int x, int y, unsigned int color);
unsigned int	get_color(int r, int g, int b);
unsigned int	get_texture_color(t_mlx_img *texture, double u, double v);
void			draw_line(int x, double wall_height, t_game_data *data,
					double wall_x);
#endif
