#include "cube3d.h"

/*
**	Side is either floor or ceiling.
*/

static t_side	ft_is_side(char *line)
{
	if (ft_strcmp(line, "F"))
		return (F);
	if (ft_strcmp(line, "C"))
		return (C);
	return (NO_SIDE);
}

static t_err   ft_parse_color_line(char *line, t_game_data *data, size_t index)
{
	/*t_side	side;

	side = ft_is_side(line);
	if (side == NO_SIDE)
		return (FALSE);
	if (side == c)
	data->colors[index].side = side;
	*/
	return (OK);
}

t_err			ft_parse_colors(int fd, t_game_data *data, char *line)
{
	return (OK);
}