#include "cube3d.h"

int	ft_error(t_err errtype, t_game_data *data)
{
	printf("Error\nCODE : %i\n", errtype);
	ft_destroy(data);
	return (1);
}
