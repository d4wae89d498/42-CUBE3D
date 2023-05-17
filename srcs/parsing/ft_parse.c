#include "cube3d.h"

e_parse_err ft_parse(int ac, char **av)
{
    if (ac != 2)
        return (WRONG_ARG_NUMBER);
    if (!ft_is_map_name_valid(av[1]))
        return (WRONG_MAP_NAME);
    return (OK);
}