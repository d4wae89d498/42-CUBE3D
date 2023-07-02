#include "cube3d.h"


/// todo also check for also syscalls error output ??
t_err ft_init(t_game_data *data)
{
   // ft_bzero(data, sizeof(t_game_ctx));

    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
           return (INITIALIZATION_ERROR);
 
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cube3d");


		data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		data->img.addr = mlx_get_data_addr(data->img.img, &(data->img.bits_per_pixel),
				&(data->img.line_length),
				&(data->img.endian));


    return (OK);
}