#include "cube3d.h"

int main(int ac, char **av)
{
    t_data      data;
    t_err       ret;

    if ((ret = ft_init(&data)) != OK)
        return (ft_error(ret, &data));
    if ((ret = ft_parse(ac, av, &data)) != OK)
        return (ft_error(ret, &data));
    ft_destroy(&data);
    return (0);
}