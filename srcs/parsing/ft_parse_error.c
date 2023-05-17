#include "cube3d.h"

int ft_parse_error(t_parse_err errtype)
{
    (void)errtype;
    write(1, "Error\n", 6);
    return (1);
}