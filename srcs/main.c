#include "cube3d.h"

int	main(int ac, char **av)
{
	t_game_data	data;
	t_err		ret;

	ret = ft_init(&data);
	if (ret != OK)
		return (ft_error(ret, &data));
	ret = ft_parse(ac, av, &data);
	if (ret != OK)
		return (ft_error(ret, &data));
	mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data);
	raycasting(&data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
