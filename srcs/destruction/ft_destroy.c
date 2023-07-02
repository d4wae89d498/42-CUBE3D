#include "cube3d.h"

static void ft_destroy_textures(t_game_data *data)
{
    size_t  i;

    i = 0;
    while (i < 4)
    {
        if (data->textures_state[i])
        {
            mlx_destroy_image(data->mlx_ptr, data->textures[i].img);
            data->textures[i].img = NULL;
        }
        i++;
    }
     mlx_destroy_image(data->mlx_ptr, data->default_texture.img);
    data->default_texture.img = NULL;
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