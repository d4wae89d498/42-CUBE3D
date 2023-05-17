#include "cube3d.h"

t_bool	ft_end_with(char *str, char *end)
{
	size_t	strlen;
	size_t	endlen;

	strlen = ft_strlen(str);
	endlen = ft_strlen(end);
	if (endlen > strlen)
		return (FALSE);
	while (endlen > 0)
	{
		if (str[strlen] != end[endlen])
			return (FALSE);
		strlen--;
		endlen--;
	}
	return (TRUE);
}

t_bool	ft_is_map_name_valid(char *map_name)
{
    size_t	last_slash_pos;
    size_t	i;

    last_slash_pos = 0;
    i = 0;
    while (map_name[i])
    {
        if (map_name[i] == '/')
            last_slash_pos = i + 1;
        i++;
    }
	if (ft_strlen(map_name + last_slash_pos) <= 4)
		return (FALSE);
	if (!ft_end_with(map_name, ".cub"))
		return (FALSE);
    return (TRUE);
}