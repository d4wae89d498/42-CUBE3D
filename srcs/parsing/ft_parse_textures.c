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
    return (NONE);
}

t_bool  ft_parse_textures(int fd, t_data *data)
{
    char        *line;
    size_t      index;
    size_t      str_index;
    t_direction direction;
    
    index = 0;
    while (index < 4)
    {
        line = get_next_line(fd);
        str_index = 0;
		direction = ft_is_direction_valid(line);
		if (direction == NONE)
			return (FALSE);
		str_index += 2 + ft_skip_whitespaces(line + 2);
        ft_strtrim_end(line + str_index);
        data->textures[direction].direction = direction;
        data->textures[direction].texture_img = mlx_xpm_file_to_image(data->mlx, (line + str_index), &(data->textures->width), &(data->textures->height));
        free(line);
        if (!(data->textures[direction].texture_img))
            return (FALSE);
        index++;
    }
    return (TRUE);
}