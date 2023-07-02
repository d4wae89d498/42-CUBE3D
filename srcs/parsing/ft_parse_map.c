#include "cube3d.h"

t_bool  ft_parse_map(int fd, t_game_data *data)
{
    char	*current_line;

    if (!ft_parse_textures(fd, data))
        return (FALSE);
   // if (!ft_skip_newlines(fd, &current_line))
//		return (FALSE);
	if (!ft_parse_colors(fd, data, current_line))
		return (FALSE);
   if (!ft_parse_map_cells(fd, data))
     return (FALSE);
	return (TRUE);
}