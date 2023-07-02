#include "cube3d.h"

t_bool  ft_parse_map(int fd, t_game_data *data)
{
	char	  *line;
	t_bool  map_started;
	t_err   state;

	map_started = FALSE;
	while ((line = get_next_line(fd)))
	{
		if (!map_started)
		{
		  if (line[0] == '\n')
		  {
			free(line);
			continue;
		  }
		  state = ft_parse_textures(fd, data, line);
		  if (state != OK && state != MATCH)
		  {
			free(line);
			return (FALSE);
		  }
		  else if (state == MATCH)
			continue ;
		  state = ft_parse_colors(fd, data, line);
		  if (state != OK && state != MATCH)
		   {
			free(line);
			return (FALSE);
		  }
		  else if (state == MATCH)
			continue ;

		  if (!map_started)
			map_started = TRUE;
		}
		if (map_started)
		{
		  if(ft_parse_map_cells(fd, data, line) != OK)
			{
			free(line);
			return (FALSE);
		  }
		}
	}
	free(line);
	if (!is_valid_map(data->map))
	{
		printf("Error\nLa carte n'est pas entourée de murs ou contient des espaces vides non entourés de murs.\n");
		return (FALSE);
	}
	return (TRUE);
}
