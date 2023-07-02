#include "cube3d.h"
#include "math.h"

static void	move_forward(t_game_data *data)
{
	double	new_player_x;
	double	new_player_y;

	new_player_x = data->player.x + data->player.dir_x * MOVE_SPEED;
	new_player_y = data->player.y + data->player.dir_y * MOVE_SPEED;
	if (data->map[(int)new_player_y][(int)data->player.x] != '1')
		data->player.y = new_player_y;
	if (data->map[(int)data->player.y][(int)new_player_x] != '1')
		data->player.x = new_player_x;
}

static void	move_backward(t_game_data *data)
{
	double	new_player_x;
	double	new_player_y;

	new_player_x = data->player.x - data->player.dir_x * MOVE_SPEED;
	new_player_y = data->player.y - data->player.dir_y * MOVE_SPEED;
	if (data->map[(int)new_player_y][(int)data->player.x] != '1')
		data->player.y = new_player_y;
	if (data->map[(int)data->player.y][(int)new_player_x] != '1')
		data->player.x = new_player_x;
}

static void	move_left(t_game_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-ROT_SPEED)
		- data->player.dir_y * sin(-ROT_SPEED);
	data->player.dir_y = old_dir_x * sin(-ROT_SPEED)
		+ data->player.dir_y * cos(-ROT_SPEED);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-ROT_SPEED)
		- data->player.plane_y * sin(-ROT_SPEED);
	data->player.plane_y = old_plane_x * sin(-ROT_SPEED)
		+ data->player.plane_y * cos(-ROT_SPEED);
}

static void	move_right(t_game_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(ROT_SPEED)
		- data->player.dir_y * sin(ROT_SPEED);
	data->player.dir_y = old_dir_x * sin(ROT_SPEED)
		+ data->player.dir_y * cos(ROT_SPEED);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(ROT_SPEED)
		- data->player.plane_y * sin(ROT_SPEED);
	data->player.plane_y = old_plane_x * sin(ROT_SPEED)
		+ data->player.plane_y * cos(ROT_SPEED);
}

int	key_press(int keycode, void *param)
{
	t_game_data	*data;

	data = (t_game_data *)param;
	printf("keycode ; %i\n", keycode);
	if (keycode == 65307)
	{
		ft_destroy(data);
		exit(0);
	}
	else if (keycode == 119)
		move_forward(data);
	else if (keycode == 115)
		move_backward(data);
	else if (keycode == 97)
		move_left(data);
	else if (keycode == 100)
		move_right(data);
	raycasting(data);
	return (0);
}
