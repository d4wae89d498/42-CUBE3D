#include "cube3d.h"

/*
**	Side is either floor or ceiling.
*/

t_err parse_color(char *line, unsigned int *color)
{
    int r = 0, g = 0, b = 0;
    unsigned int value = 0;
    int count = 0;
    int i = 0;
    int start = 0;
	
	i += ft_skip_whitespaces(line);
	
    while (line[i])
    {
        if (line[i] == ',' || line[i] == '\n')
        {
            if (start == 1)
            {
                if (count > 2)
				{
 			printf("aa %i\n", value);
   
	                return (MAP_ERROR);
				}
			
            }
            start = 0;
        }

		if ((line[i] < '0' || line[i] > '9'))
					return (MAP_ERROR);
		value = 0;
        while (line[i] >= '0' && line[i] <= '9')
        {
            value = value * 10 + (line[i] - '0');
            start = 1;
			i += 1;
			if (value > 255)
			{
				return (MAP_ERROR);
			}

        }
		
		if (count == 0)
			r = value;
		else if (count == 1)
			g = value;
		else if (count == 2)
			b = value;
		
		printf("color=%i\n", value);


		if ((count == 0 || count == 1) && line[i] != ',')
			return (MAP_ERROR);
		
		if ((count == 2) && line[i] != '\n')
			return (MAP_ERROR);
			
		i += 1;
		
		count += 1;
       

    }

	printf("count=%i\n", count);
    if (count != 3)
        return (MAP_ERROR);

	printf("r %i, g %i, b %i\n", r, g, b);
	*color = get_color(r, g, b);
	printf("count=%i | color=%i\n", count, *color);

    return OK;
}

t_err			ft_parse_colors(int fd, t_game_data *data, char *line)
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