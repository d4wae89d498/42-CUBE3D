#include "cube3d.h"


/// todo also check for also syscalls error output ??
// TODO ALSO destroy default texture
t_err ft_init(t_game_data *data)
{
	int	 i;
	int	 j;

	ft_bzero(data, sizeof(t_game_data));

	data->floor_color = DEFAULT_FLOOR_COLOR;
	data->sky_color = DEFAULT_SKY_COLOR;
	data->floor_set = FALSE;
	data->sky_set = FALSE;

	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		   return (INITIALIZATION_ERROR);

	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cube3d");


		data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		data->img.addr = mlx_get_data_addr(data->img.img, &(data->img.bits_per_pixel),
				&(data->img.line_length),
				&(data->img.endian));


 data->default_texture.img = mlx_xpm_file_to_image(data->mlx_ptr, DEFAULT_TEXTURE,
 &(data->default_texture.width), &(data->default_texture.height));
  		if (!(data->default_texture.img))
		return (INITIALIZATION_ERROR);
	data->default_texture.addr = mlx_get_data_addr(data->default_texture.img,
	&(data->default_texture.bits_per_pixel), &(data->default_texture.line_length), &(data->default_texture.endian));

	i = 0;
	while (i < 4)
	{
		data->textures[i] = data->default_texture;
		i += 1;
	}


	while (i < MAX_MAP_HEIGHT)
	{
		j = 0;
		while (j < MAX_MAP_WIDTH)
		{
			 data->map[i][j] = ' ';
			j += 1;
		}
		i += 1;
	}

	return (OK);
}
