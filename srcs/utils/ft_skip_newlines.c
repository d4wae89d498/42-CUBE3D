#include "cube3d.h"

/*
**  This function make sure theres is at least one empty newline on the fd,
**      if not return FALSE
**      set current_line to next non empty line;
**      return TRUE if everythings good;
*/

t_bool  ft_skip_newlines(int fd, char **current_line)
{
    size_t  index;

    index = 0;
    while ((*current_line = get_next_line(fd)))
    {
        if ((*current_line)[0] != '\n')
        {
            if (index == 0)
                return (FALSE);
            return (TRUE);
        }
        index++;
    }
}