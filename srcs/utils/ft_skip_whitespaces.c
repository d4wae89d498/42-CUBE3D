#include "cube3d.h"

void    ft_skip_whitespaces(char **str)
{
    while (**str && (**str == ' '))
        (*str)++;
}