#include "cube3d.h"

static const char *ERROR_STR[] = {
    "OK",
	"INITIALIZATION_ERROR",
    "WRONG_ARG_NUMBER",
	"WRONG_MAP_NAME",
	"OPEN_ERROR",
	"MAP_ERROR"
};

int ft_error(t_err errtype)
{
    printf("Error\nCODE : %s\n", ERROR_STR[errtype]);
    return (1);
}