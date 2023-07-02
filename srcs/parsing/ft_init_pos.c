#include "cube3d.h"

static void	init_base_position_n(t_game_data *data, int col, int row)
{
	data->player.x = col + 0.5;
	data->player.y = row + 0.5;
	data->player.dir_x = 1.0;
	data->player.dir_y = 0.0;
	data->player.plane_x = 0.0;
	data->player.plane_y = 0.66;
}

static void	init_base_position_s(t_game_data *data, int col, int row)
{
	data->player.x = col + 0.5;
	data->player.y = row + 0.5;
	data->player.dir_x = -1.0;
	data->player.dir_y = 0.0;
	data->player.plane_x = 0.0;
	data->player.plane_y = -0.66;
}

static void	init_base_position_e(t_game_data *data, int col, int row)
{
	data->player.x = col + 0.5;
	data->player.y = row + 0.5;
	data->player.dir_x = 0.0;
	data->player.dir_y = 1.0;
	data->player.plane_x = -0.66;
	data->player.plane_y = 0.0;
}

static void	init_base_position_w(t_game_data *data, int col, int row)
{
	data->player.x = col + 0.5;
	data->player.y = row + 0.5;
	data->player.dir_x = 0.0;
	data->player.dir_y = -1.0;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0.0;
}

void	init_base_position(t_game_data *data, char c, int col, int row)
{
	data->player.x = col + 0.5;
	data->player.y = row + 0.5;
	if (c == 'N')
		init_base_position_n(data, col, row);
	else if (C == 'S')
	{
		init_base_position_s(data, col, row);
	}
	else if (c == 'E')
	{
		init_base_position_e(data, col, row);
	}
	else
	{
		init_base_position_w(data, col, row);
	}
}
