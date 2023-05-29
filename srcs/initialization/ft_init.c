#include "cube3d.h"

t_err ft_init(t_data *data)
{
    ft_bzero(data, sizeof(t_data));
    data->mlx = mlx_init();
    if (!data->mlx)
        return (INITIALIZATION_ERROR);
    return (OK);
}