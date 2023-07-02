#include "cube3d.h"

static void ft_destroy_textures(t_game_data *data)
{
    size_t  i;

    i = 0;
    while (i < 4)
    {
        if (data->textures[i].img)
        {
            mlx_destroy_image(data->mlx_ptr, data->textures[i].img);
            data->textures[i].img = NULL;
        }
        i++;
    }
}

void    ft_destroy(t_game_data *data)
{
    ft_destroy_textures(data);
    if (data->mlx_ptr)
    {
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
        data->mlx_ptr = NULL;
    }
}