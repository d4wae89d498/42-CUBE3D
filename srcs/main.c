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


    //data.player.x = 16;
    //data.player.y = 2;




    mlx_hook(data.win_ptr, 2, 1L << 0, key_press, &data );

    raycasting(&data );
    
    mlx_loop(data.mlx_ptr);
    
    return (0);
}
