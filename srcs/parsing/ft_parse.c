#include "cube3d.h"

static t_err	ft_close_and_return(int fd, t_err errtype)
{
	close(fd);
	return (errtype);
}

t_err	ft_parse(int ac, char **av, t_game_data *data)
{
    int fd;

    if (ac != 2)
        return (WRONG_ARG_NUMBER);
    if (!ft_is_map_name_valid(av[1]))
        return (WRONG_MAP_NAME);
    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        return (OPEN_ERROR);
    if (!ft_parse_map(fd, data))
		return (ft_close_and_return(fd, MAP_ERROR));
	return (ft_close_and_return(fd, OK));
}