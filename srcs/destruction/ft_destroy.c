#include "cube3d.h"

static void ft_destroy_textures(t_data *data)
{
    size_t  i;

    i = 0;
    while (i < 4)
    {
        if (data->textures[i].texture_img)
        {
            mlx_destroy_image(data->mlx, data->textures[i].texture_img);
            data->textures[i].texture_img = NULL;
        }
        i++;
    }
}

void    ft_destroy(t_data *data)
{
    ft_destroy_textures(data);
    if (data->mlx)
    {
        free(data->mlx);
        data->mlx = NULL;
    }
}