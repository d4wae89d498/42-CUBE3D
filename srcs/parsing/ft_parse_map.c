#include "cube3d.h"




t_bool  ft_parse_map(int fd, t_game_data *data)
{
    char	  *line;
    t_bool  map_started;
    t_err   state;

    map_started = FALSE;
    while ((line = get_next_line(fd)))
    {
        if (!map_started)
        {
          if (line[0] == '\n')
          {
            free(line);
            continue;
          }
          state = ft_parse_textures(fd, data, line);
          if (state != OK && state != MATCH)
          {
            free(line);
            return (FALSE);	
          }
          else if (state == MATCH)
            continue ;


          state = ft_parse_colors(fd, data, line);
          if (state != OK && state != MATCH)
           {
            free(line);
            return (FALSE);	
          }
          else if (state == MATCH)
            continue ;

          if (!map_started)
            map_started = TRUE;
        }

        if (map_started)
        {
          if(ft_parse_map_cells(fd, data, line) != OK)
            {
            free(line);
            return (FALSE);	
          }
        }
        
    }




    free(line); 



    // Vérifier si la carte est entourée de murs
    if (!is_valid_map(data->map))
    {
        printf("Error\nLa carte n'est pas entourée de murs ou contient des espaces vides non entourés de murs.\n");
        return (FALSE);
    }


    // Afficher la carte
    for (int i = 0; i < MAX_MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAX_MAP_WIDTH; j++)
        {
            printf("%c ", data->map[i][j]);
        }
        printf("\n");
    }

    // Afficher la position et l'orientation du joueur
    printf("Position du joueur : x = %f, y = %f\n", data->player.x, data->player.y);
  //  printf("Orientation du joueur : %c\n", player_orientation);

	  return (TRUE);
}