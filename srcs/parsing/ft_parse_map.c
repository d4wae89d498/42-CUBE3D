#include "cube3d.h"

t_bool  ft_parse_map(int fd, t_data *data)
{
    if (!ft_parse_textures(fd, data))
        return (FALSE);
    return (TRUE);
}