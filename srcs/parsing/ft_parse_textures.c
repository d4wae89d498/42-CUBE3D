#include "cube3d.h"

static t_direction  ft_is_direction_valid(char *line)
{
    if (line[0] == 'N' && line[1] == 'O')
        return (NORTH);
    if (line[0] == 'S' && line[1] == 'O')
        return (SOUTH);
    if (line[0] == 'E' && line[1] == 'A')
        return (EAST);
    if (line[0] == 'W' && line[1] == 'E')
        return (WEST);
    return (NONE);
}


// toddo :: allow more flexibility
t_err  ft_parse_textures(int fd, t_game_data *data, char *line)
{
printf("parse texture : [%s]\n", line);
    size_t      str_index;
    t_direction direction;

    str_index = 0;
    direction = ft_is_direction_valid(line);
    printf("dir=%i\n", direction);
    if (direction == NONE)
		return (OK);
    if ( data->textures_state[direction - 1] )
    {
        printf("Texture already set!!");
        return (MAP_ERROR);
    }


	str_index += 2 + ft_skip_whitespaces(line + 2);
    ft_strtrim_end(line + str_index);

    data->textures_state[direction - 1] = TRUE;
    data->textures[direction - 1].img = mlx_xpm_file_to_image(data->mlx_ptr, (line + str_index), &(data->textures[direction - 1].width), &(data->textures[direction - 1].height));
  	if (!(data->textures[direction - 1].img))
        return (MAP_ERROR); 
    data->textures[direction - 1].addr = mlx_get_data_addr(data->textures[direction - 1].img, &(data->textures[direction - 1].bits_per_pixel), &(data->textures[direction - 1].line_length), &(data->textures[direction - 1].endian));
 
 printf("end!\n");
 // todo :: looks useless bellow
 //data->textures[index].height = 512; 

// data->textures[index].width = 512; 

    return (MATCH);
}