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
	return (NONE);
}

static t_bool   ft_parse_color_line(char *line, t_data *data, size_t index)
{
	t_side	side;

	side = ft_is_side(line);
	if (side == NONE)
		return (FALSE);
	data->colors[index].side = side;
	
	return (TRUE);
}

t_bool			ft_parse_colors(int fd, t_data *data, char *line)
{

}