#include "cube3d.h"


#include <math.h>

int main(int ac, char **av)
{

    t_game_data data;   
    t_err       ret;
    
    if ((ret = ft_init(&data )) != OK)
        return (ft_error(ret, &data ));
    if ((ret = ft_parse(ac, av, &data )) != OK)
        return (ft_error(ret, &data ));


    data.player.x = 16;
    data.player.y = 2;


    data.player.dir_x = 0.0;
    data.player.dir_y = 1.0;
    data.player.plane_x = 0.66;
    data.player.plane_y = 0.0;

    mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data );

    raycasting(&data );
    
    mlx_loop(data.mlx_ptr);
    
    return (0);
}
