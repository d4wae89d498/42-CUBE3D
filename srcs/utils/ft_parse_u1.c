#include "cube3d.h"

static t_bool	ft_is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

t_bool			ft_parse_u1(char *number, t_u1 *out)
{
	size_t	i;
	int		temp_out;
	t_bool	ret;

	i = 0;
	temp_out = 0;
	while (ft_is_digit(number[i]))
	{
		temp_out *= 10;
		temp_out += (number[i] - '0');
		if (temp_out > 255)
			return (FALSE);
		i++;
	}
	*out = (t_u1)temp_out;
	return (i != 0);
}