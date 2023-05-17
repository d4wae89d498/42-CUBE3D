#include "cube3d.h"

int main(int ac, char **av)
{
    t_map       map;
    t_parse_err parse_ret;

    if ((parse_ret = ft_parse(ac, av, &map)) != OK)
        return (ft_parse_error(parse_ret));
    return (0);
}