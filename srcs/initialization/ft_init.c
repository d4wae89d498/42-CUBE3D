#include "cube3d.h"

t_err ft_init(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        return (INITIALIZATION_ERROR);
    data->textures[0].direction = NONE;
    data->textures[1].direction = NONE;
    data->textures[2].direction = NONE;
    data->textures[3].direction = NONE;
    return (OK);
}