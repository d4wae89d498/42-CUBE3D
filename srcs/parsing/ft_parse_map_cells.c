#include "cube3d.h"


static int check_map_boundaries(int x, int y)
{
    if (x < 0 || y < 0 || x >= MAX_MAP_WIDTH || y >= MAX_MAP_HEIGHT)
        return 1;
    return 0;
}

t_bool is_valid_map(char map[MAX_MAP_HEIGHT][MAX_MAP_WIDTH])
{
    // Vérifier si la carte est entourée de murs
    for (int y = 0; y < MAX_MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_MAP_WIDTH; x++)
        {
            if (map[y][x] == '0')
            {
               // printf("y=%i x=%i\n", y, x);
                // Vérifier les 4 cellules voisines
                if (check_map_boundaries(x - 1, y) || map[y][x - 1] == ' ')
                    return 0;
                if (check_map_boundaries(x + 1, y) || map[y][x + 1] == ' ')
                    return 0;
                if (check_map_boundaries(x, y - 1) || map[y - 1][x] == ' ')
                    return 0;
                if (check_map_boundaries(x, y + 1) || map[y + 1][x] == ' ')
                    return 0;
            }
        }
    }

    return 1;
}

// todo : apperler destroy quand pb
t_err ft_parse_map_cells(int fd, t_game_data *data, char *line)
{
    static int row = 0;



        printf("LINE[%i]=%s\n", row, line);
        if (row >= MAX_MAP_HEIGHT)
        {
            printf("Error\nLa carte dépasse la hauteur maximale autorisée.\n");
            free(line);
            return (MAP_ERROR);
        }

        int line_length = ft_strlen(line);
        if (line_length >= MAX_MAP_WIDTH)
        {
            printf("Error\nLa carte dépasse la largeure maximale autorisée.\n");
            free(line);
            return (MAP_ERROR);
         }


        int nonempty = 0;

        int col = 0;

        while (line[col])
        {
            char c = line[col];
            if (!nonempty && c == '\n' && get_next_line(fd))
            {
                printf("Error\nLa carte ne peux pas contenir un saut de ligne dans la description!\n");
                free(line);
            return (MAP_ERROR);
            }
            if (c == '\n' || !c)
                break;
            if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')
            {
                printf("Error\nCaractère invalide dans la map : '%c'\n", c);
                free(line);
            return (MAP_ERROR);
            }
            if (c != ' ')
                nonempty += 1;

            data->map[row][col] = c;

            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                data->player.x = col + 0.5;
                data->player.y = row + 0.5;
                // TODO : check for player dir
            }

            col += 1;
        }

        if (nonempty)
            row++;
       
 


    return (OK);
}
