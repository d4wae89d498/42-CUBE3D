#include "cube3d.h"

t_err	parse_color_char(char *line, int *i, int *value, int count)
{
	if ((line[*i] < '0' || line[*i] > '9'))
		return (MAP_ERROR);
	*value = 0;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		*value = *value * 10 + (line[*i] - '0');
		*i += 1;
		if (*value > 255)
			return (MAP_ERROR);
	}
	if (!((count < 2 && line[*i] == ',') || line[*i] == '\n'))
		return (MAP_ERROR);
	return (OK);
}

t_err	parse_color_char_w(char *line, int *i, t_color *color, int count)
{
	int	value;

	if (parse_color_char(line, i, &value, count) != OK)
		return (MAP_ERROR);
	if (count == 0)
		color->r = value;
	else if (count == 1)
		color->g = value;
	else if (count == 2)
		color->b = value;
	if ((count == 0 || count == 1) && line[*i] != ',')
		return (MAP_ERROR);
	if ((count == 2) && line[*i] != '\n')
		return (MAP_ERROR);
	return (OK);
}

/*
**	Side is either floor or ceiling.
*/

t_err	parse_color(char *line, unsigned int *color)
{
	t_color			ccolor;
	int				count;
	int				i;
	int				value;

	count = 0;
	i = ft_skip_whitespaces(line);
	while (line[i])
	{
		parse_color_char_w(line, &i, &ccolor, count);
		i += 1;
		count += 1;
	}
	if (count != 3)
		return (MAP_ERROR);
	*color = get_color(ccolor.r, ccolor.g, ccolor.b);
	return (OK);
}

t_err	ft_parse_colors(int fd, t_game_data *data, char *line)
{
	t_err			out;
	unsigned int	color;

	if (line[0] == 'F')
	{
		if (data->floor_set)
			return (MAP_ERROR);
		data->floor_set = TRUE;
		out = parse_color(line + 1, &data->floor_color);
		if (out == OK)
			return (MATCH);
		return (MAP_ERROR);
	}
	if (line[0] == 'C')
	{
		if (data->sky_set)
			return (MAP_ERROR);
		data->sky_set = TRUE;
		out = parse_color(line + 1, &data->sky_color);
		if (out == OK)
			return (MATCH);
		return (MAP_ERROR);
	}
	return (OK);
}
