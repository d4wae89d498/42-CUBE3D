#include "cube3d.h"

void	draw_line(int x, double wall_height, t_game_data *data,
	double wall_x)
{
	int				start;
	int				end;
	int				y;
	double			wall_tex_pos;
	unsigned int	tex_color;

	start = (HEIGHT - wall_height) / 2;
	end = start + wall_height;
	y = 0;
	while (y < start)
		ft_mlx_pixel(data->img, x, y++, data->sky_color);
	while (y < end && y < HEIGHT)
	{
		wall_tex_pos = (y - start) / wall_height;
		tex_color = get_texture_color(&data->textures[
				data->parser.texture_index],
				wall_x, wall_tex_pos);
		ft_mlx_pixel(data->img, x, y++, tex_color);
	}
	while (y < HEIGHT)
		ft_mlx_pixel(data->img, x, y++, data->floor_color);
}
