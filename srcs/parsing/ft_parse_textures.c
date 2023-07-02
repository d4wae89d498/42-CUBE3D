#include "cube3d.h"

static t_direction  ft_is_direction_valid(char *line)
{
    if (ft_strcmp(line, "NO"))
        return (NORTH);
    if (ft_strcmp(line, "SO"))
        return (SOUTH);
    if (ft_strcmp(line, "EA"))
        return (EAST);
    if (ft_strcmp(line, "WE"))
        return (WEST);
    return (NONE);
}

t_bool  ft_parse_texture_line(char *line, t_game_data *data, size_t index)
{
    size_t      str_index;
    t_direction direction;

    str_index = 0;
    direction = ft_is_direction_valid(line);
    if (direction == NONE)
		return (FALSE);
	str_index += 2 + ft_skip_whitespaces(line + 2);
    ft_strtrim_end(line + str_index);
    data->textures[direction - 1].img = mlx_xpm_file_to_image(data->mlx_ptr, (line + str_index), &(data->textures[direction - 1].width), &(data->textures[direction - 1].height));
  	    if (!(data->textures[index].img))
        return (FALSE); 
    data->textures[direction - 1].addr = mlx_get_data_addr(data->textures[direction - 1].img, &(data->textures[direction - 1].bits_per_pixel), &(data->textures[direction - 1].line_length), &(data->textures[index].endian));
 
 // todo :: looks useless bellow
 //data->textures[index].height = 512; 

// data->textures[index].width = 512; 
    
    return (TRUE);
}

// toddo :: allow more flexibility
t_bool  ft_parse_textures(int fd, t_game_data *data)
{
    char        *line;
    size_t      index;
    t_bool      ret;

    index = 0;
    while (index < 4)
    {
        line = get_next_line(fd);
        ret = ft_parse_texture_line(line, data, index);
        free(line);
        if (ret == FALSE)
            return (FALSE);
        index++;
    }
    return (TRUE);
}