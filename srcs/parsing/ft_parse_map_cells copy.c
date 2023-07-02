#include "cube3d.h"

static int	check_map_boundaries(int x, int y)
{
	if (x < 0 || y < 0 || x >= MAX_MAP_WIDTH || y >= MAX_MAP_HEIGHT)
		return (1);
	return (0);
}

t_bool	is_valid_map(char map[MAX_MAP_HEIGHT][MAX_MAP_WIDTH])
{
	int	y;
	int	x;

	y = 0;
	while (y < MAX_MAP_HEIGHT)
	{
		x = 0;
		while (x < MAX_MAP_WIDTH)
		{
			if (map[y][x++] == '0')
			{
				if (check_map_boundaries(x - 1, y) || map[y][x - 1] == ' ')
					return (0);
				if (check_map_boundaries(x + 1, y) || map[y][x + 1] == ' ')
					return (0);
				if (check_map_boundaries(x, y - 1) || map[y - 1][x] == ' ')
					return (0);
				if (check_map_boundaries(x, y + 1) || map[y + 1][x] == ' ')
					return (0);
			}
		}
		y += 1;
	}
	return (1);
}

t_err	check_map_dimensions(char *line, int row)
{
	if (ft_strlen(line) >= MAX_MAP_WIDTH)
		return (ft_sfr(line, MAP_ERROR));
	if (row >= MAX_MAP_HEIGHT)
		return (ft_sfr(line, MAP_ERROR));
	return (OK);
}

t_err	ft_parse_c(t_game_data *data, char *line, int col, int row)
{
	static t_bool	found_pos;
	char			c;

	c = line[col];
	if (!data->parser.nonempty && c == '\n'
		&& get_next_line(data->parser.fd))
		return (ft_sfr(line, MAP_ERROR));
	if (c == '\n' || !c)
		return (MATCH);
	if (c != '0' && c != '1' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != ' ')
		return (ft_sfr(line, MAP_ERROR));
	if (c != ' ')
		data->parser.nonempty += 1;
	data->map[row][col] = c;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (found_pos)
			return (ft_sfr(line, MAP_ERROR));
		found_pos = TRUE;
		init_base_position(data, c, col, row);
	}
}

t_err	ft_parse_map_cells(int fd, t_game_data *data, char *line)
{
	static int	row;
	int			nonempty;
	int			col;
	t_err		r;

	if (check_map_dimensions(line, row) != OK)
		return (MAP_ERROR);
	data->parser.fd = fd;
	data->parser.nonempty = 0;
	col = 0;
	while (line[col])
	{
		r = ft_parse_c(data, line, col, row);
		if (r == MATCH)
			break ;
		if (r != OK)
			return (MAP_ERROR);
		col += 1;
	}
	if (data->parser.nonempty)
		row++;
	return (OK);
}
