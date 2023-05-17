#include "cube3d.h"

t_bool  ft_strcmp(char *s1, char *s2)
{
    size_t  i;

    i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (FALSE);
        i++;
    }
    return (TRUE);
}