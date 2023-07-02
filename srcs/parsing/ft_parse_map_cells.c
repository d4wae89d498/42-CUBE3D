#include "cube3d.h"


static int check_map_boundaries(int x, int y)
{
    if (x < 0 || y < 0 || x >= MAX_MAP_WIDTH || y >= MAX_MAP_HEIGHT)
        return 1;
    return 0;
}

static int is_valid_map(char map[MAX_MAP_HEIGHT][MAX_MAP_WIDTH])
{
    // Vérifier si la carte est entourée de murs
    for (int y = 0; y < MAX_MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_MAP_WIDTH; x++)
        {
            if (map[y][x] == '0')
            {
                printf("y=%i x=%i\n", y, x);
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
int ft_parse_map_cells(int fd, t_game_data *data)
{
    char *line;
    int i;
    int j;
    int player_orientation;

    i = 0;
    while (i < MAX_MAP_HEIGHT)
    {
        j = 0;
        while (j < MAX_MAP_WIDTH)
        {
             data->map[i][j] = ' ';
            j += 1;
        }
        i += 1;
    }

    // Lire la carte et stocker les données dans le tableau
    int row = 0;

    int new_line_skipped = FALSE;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] == '\n' && !new_line_skipped)
        {
            free(line);
            continue ;
        }
        new_line_skipped = TRUE;

        printf("LINE[%i]=%s\n", row, line);
        if (row >= MAX_MAP_HEIGHT)
        {
            printf("Error\nLa carte dépasse la hauteur maximale autorisée.\n");
            free(line);
            return (FALSE);
        }

        int line_length = ft_strlen(line);
        if (line_length >= MAX_MAP_WIDTH)
        {
            printf("Error\nLa carte dépasse la largeure maximale autorisée.\n");
            free(line);
            return (FALSE);   
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
                return (FALSE);
            }
            if (c == '\n' || !c)
                break;
            if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')
            {
                printf("Error\nCaractère invalide dans la map : '%c'\n", c);
                free(line);
                return (FALSE);
            }
            if (c != ' ')
                nonempty += 1;

            data->map[row][col] = c;

            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                data->player.x = col + 0.5;
                data->player.y = row + 0.5;
                // TODO : check for player dir
                player_orientation = c;
            }

            col += 1;
        }

        free(line);

        if (nonempty)
            row++;
       
    }

    // Vérifier si la carte est entourée de murs
    if (!is_valid_map(data->map))
    {
        printf("Error\nLa carte n'est pas entourée de murs ou contient des espaces vides non entourés de murs.\n");
        return (FALSE);
    }


    // Afficher la carte
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < MAX_MAP_WIDTH; j++)
        {
            printf("%c ", data->map[i][j]);
        }
        printf("\n");
    }

    // Afficher la position et l'orientation du joueur
    printf("Position du joueur : x = %f, y = %f\n", data->player.x, data->player.y);
    printf("Orientation du joueur : %c\n", player_orientation);

    return TRUE;
}
