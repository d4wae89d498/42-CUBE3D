#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 512
#define MAP_WIDTH 100
#define MAP_HEIGHT 100

char *get_next_line(int fd);

int check_map_boundaries(int x, int y)
{
    if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT)
        return 1;
    return 0;
}

int is_valid_map(char map[][MAP_WIDTH])
{
    // Vérifier si la carte est entourée de murs
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (map[y][x] == '0')
            {
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

int main()
{
    int fd;
    char *line;
    char map[MAP_HEIGHT][MAP_WIDTH];
    int player_x, player_y;
    char player_orientation;

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
             map[i][j] = ' ';
        }
    }

    // Ouvrir le fichier .cub
    fd = open("mine.cub", O_RDONLY);
    if (fd == -1)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Lire la carte et stocker les données dans le tableau
    int row = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        
        if (row >= MAP_HEIGHT)
        {
            printf("La carte dépasse la hauteur maximale autorisée.\n");
            free(line);
            close(fd);
            return 1;
        }

        int line_length = strlen(line);
      /*  if (line_length != MAP_WIDTH)
        {
            printf("La largeur de la ligne ne correspond pas à la largeur de la carte.\n");
            free(line);
            close(fd);
            return 1;
        }*/

        int nonempty = 0;

        for (int col = 0; col < MAP_WIDTH; col++)
        {
            char c = line[col];
            if (!nonempty && c == '\n' && get_next_line(fd))
            {
                printf("erreur, la carte ne peux pas contenir un saut de ligne dans la description!\n");
                exit(0);
            }
            if (c == '\n' || !c)
                break;
            if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')
            {
                printf("Caractère invalide dans la map : '%c'\n", c);
                free(line);
                close(fd);
                return 1;
            }
            if (c != ' ')
                nonempty += 1;

            map[row][col] = c;

            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                player_x = col;
                player_y = row;
                player_orientation = c;
            }
        }

        free(line);
        row++;
    }
/*
    if (row < MAP_HEIGHT)
    {
        printf("La carte est plus petite que la hauteur spécifiée.\n");
        close(fd);
        return 1;
    }
*/
    // Vérifier si la carte est entourée de murs
    if (!is_valid_map(map))
    {
        printf("La carte n'est pas entourée de murs ou contient des espaces vides non entourés de murs.\n");
        close(fd);
        return 1;
    }

    // Fermer le fichier
    close(fd);

    // Afficher la carte
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }

    // Afficher la position et l'orientation du joueur
    printf("Position du joueur : x = %d, y = %d\n", player_x, player_y);
    printf("Orientation du joueur : %c\n", player_orientation);

    return 0;
}
