#include "cube3d.h"

static const char *ERROR_STR[] = {
    "OK",
	"INITIALIZATION_ERROR",
    "WRONG_ARG_NUMBER",
	"WRONG_MAP_NAME",
	"OPEN_ERROR",
	"MAP_ERROR"
};

int ft_error(t_err errtype, t_game_data *data)
{
    printf("Error\nCODE : %s\n", ERROR_STR[errtype]);
    ft_destroy(data);
    return (1);
}