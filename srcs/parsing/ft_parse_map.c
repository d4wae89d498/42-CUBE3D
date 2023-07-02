#include "cube3d.h"

t_bool	ft_parse_map1(char *line, int fd, t_game_data *data)
{
	t_err		state;
	static int	map_started;

	if (!map_started)
	{
		if (line[0] == '\n')
			return (TRUE);
		state = ft_parse_textures(fd, data, line);
		if (state != OK && state != MATCH)
			return (FALSE);
		else if (state == MATCH)
			return (TRUE);
		state = ft_parse_colors(fd, data, line);
		if (state != OK && state != MATCH)
			return (FALSE);
		else if (state == MATCH)
			return (TRUE);
		if (!map_started)
			map_started = TRUE;
	}
	if (map_started && (ft_parse_map_cells(fd, data, line) != OK))
		return (FALSE);
	return (TRUE);
}

t_bool	ft_parse_map(int fd, t_game_data *data)
{
	char	*line;
	t_bool	state;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		state = ft_parse_map1(line, fd, data);
		free(line);
		if (!state)
			return (FALSE);
	}
	if (!is_valid_map(data->map))
		return (FALSE);
	if (!data->textures_state[0] || !data->textures_state[1]
		|| !data->textures_state[2] || !data->textures_state[3]
		|| !data->floor_set || !data->sky_set)
		return (FALSE);
	return (TRUE);
}
