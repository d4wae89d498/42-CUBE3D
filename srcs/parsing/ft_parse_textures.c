#include "cube3d.h"

t_direction  ft_is_direction_valid(char *line)
{
    if (ft_strcmp(line, "NO"))
        return (NO);
    if (ft_strcmp(line, "SO"))
        return (SO);
    if (ft_strcmp(line, "EA"))
        return (EA);
    if (ft_strcmp(line, "WE"))
        return (WE);
    return (NOT_VALID);
}

t_bool  ft_parse_textures(int fd, t_map *map)
{
    char        *line;
    t_direction direction;
    
    while (line = get_next_line(fd))
    {
		direction = ft_is_direction_valid(line);
		if (direction == NOT_VALID)
			return (FALSE);
		line += 2;
		ft_skip_whitespaces(&line);
		// TODO CONTINUE HERE
    }
    return (TRUE);
}