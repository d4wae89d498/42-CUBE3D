#include "cube3d.h"

void ft_strtrim_end(char *str)
{
    size_t idx;

    idx = ft_strlen(str);
    if (idx > 0)
        idx--;
    while ((str[idx] == ' ' || str[idx] == '\n') && idx != 0)
        idx--;
    str[idx + 1] = 0;
}