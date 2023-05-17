#include "cube3d.h"

t_bool  ft_parse_map(int fd, t_map *map)
{
    if (!ft_parse_textures(fd, map))
        return (FALSE);
    return (TRUE);
}