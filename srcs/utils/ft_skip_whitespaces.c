#include "cube3d.h"

size_t  ft_skip_whitespaces(char *str)
{
    size_t i;

    i = 0;
    while (str[i] && str[i] == ' ')
        i++;
    return (i);
}