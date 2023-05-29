#include "cube3d.h"

void    ft_bzero(void *data, size_t n)
{
    size_t  i;

    i = 0;
	while (i < n)
	{
		((char *)data)[i] = 0;
		i++;
	}
}