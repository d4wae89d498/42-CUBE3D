#include "cube3d.h"

int ft_error(t_err errtype)
{
    write(2, "Error\n", 6);
    printf("CODE : %d\n", errtype);
    return (1);
}