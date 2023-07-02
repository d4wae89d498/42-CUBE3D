
#include "cube3d.h"
#include "math.h"

void move_player(int keycode, t_game_data *data)
{
    double move_speed = 0.10;
    double rot_speed = 0.10;

    if (keycode == 119) // W
    {
        double new_player_x = data->player.x + data->player.dir_x * move_speed;
        double new_player_y = data->player.y + data->player.dir_y * move_speed;

        if (data->map[(int)new_player_y][(int)data->player.x] != '1')
            data->player.y = new_player_y;
        if (data->map[(int)data->player.y][(int)new_player_x] != '1')
            data->player.x = new_player_x;
    }
    else if (keycode == 115) // S
    {
        double new_player_x = data->player.x - data->player.dir_x * move_speed;
        double new_player_y = data->player.y - data->player.dir_y * move_speed;

        if (data->map[(int)new_player_y][(int)data->player.x] != '1')
            data->player.y = new_player_y;
        if (data->map[(int)data->player.y][(int)new_player_x] != '1')
            data->player.x = new_player_x;
    }
    else if (keycode == 97) // D
    {
        double old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(-rot_speed) - data->player.dir_y * sin(-rot_speed);
        data->player.dir_y = old_dir_x * sin(-rot_speed) + data->player.dir_y * cos(-rot_speed);
        double old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(-rot_speed) - data->player.plane_y * sin(-rot_speed);
        data->player.plane_y = old_plane_x * sin(-rot_speed) + data->player.plane_y * cos(-rot_speed);
    }
    else if (keycode == 100) // A
    {
        double old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(rot_speed) - data->player.dir_y * sin(rot_speed);
        data->player.dir_y = old_dir_x * sin(rot_speed) + data->player.dir_y * cos(rot_speed);
        double old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(rot_speed) - data->player.plane_y * sin(rot_speed);
        data->player.plane_y = old_plane_x * sin(rot_speed) + data->player.plane_y * cos(rot_speed);
    }

    printf("KEY PRESS!\n");
    raycasting(data);
}


/*
void move_player(int keycode, t_game_data *data )
{
    double move_speed;
    double rot_speed;

    move_speed = 0.10;
    rot_speed = 0.10;

    if (keycode == 119) // W
    {
        printf("y %i y %i\n", (int)(data->player.y + data->player.dir_y * move_speed), (int)data->player.x);
        printf("%i %c\n", data->map[(int)(data->player.y + data->player.dir_y * move_speed)][(int)data->player.x], 
        data->map[(int)(data->player.y + data->player.dir_y * move_speed)][(int)data->player.x]
        );
        if (data->map[(int)(data->player.y + data->player.dir_y * move_speed)][(int)data->player.x] == '0')
            data->player.y += data->player.dir_y * move_speed;
        if (data->map[(int)data->player.y][(int)(data->player.x + data->player.dir_x * move_speed)] == '0')
            data->player.x += data->player.dir_x * move_speed;
    }
    else if (keycode == 115) // S
    {
        if (data->map[(int)(data->player.y - data->player.dir_y * move_speed)][(int)data->player.x] == '0')
            data->player.y -= data->player.dir_y * move_speed;
        if (data->map[(int)data->player.y][(int)(data->player.x - data->player.dir_x * move_speed)] == '0')
            data->player.x -= data->player.dir_x * move_speed;
    }
    else if (keycode == 100) // D
    {
        double old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(-rot_speed) - data->player.dir_y * sin(-rot_speed);
        data->player.dir_y = old_dir_x * sin(-rot_speed) + data->player.dir_y * cos(-rot_speed);
        double old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(-rot_speed) - data->player.plane_y * sin(-rot_speed);
        data->player.plane_y = old_plane_x * sin(-rot_speed) + data->player.plane_y * cos(-rot_speed);
    }
    else if (keycode == 97) // A
    {
        double old_dir_x = data->player.dir_x;
        data->player.dir_x = data->player.dir_x * cos(rot_speed) - data->player.dir_y * sin(rot_speed);
        data->player.dir_y = old_dir_x * sin(rot_speed) + data->player.dir_y * cos(rot_speed);
        double old_plane_x = data->player.plane_x;
        data->player.plane_x = data->player.plane_x * cos(rot_speed) - data->player.plane_y * sin(rot_speed);
        data->player.plane_y = old_plane_x * sin(rot_speed) + data->player.plane_y * cos(rot_speed);
    }
    printf("KEY PRESS!\n");
    raycasting(data );
}*/

int key_press(int keycode, void *param)
{
    t_game_data *data ;

    data = (t_game_data *)param;
    printf("keycode ; %i\n", keycode);
    //todo : free b4 exit
    if (keycode == 65307) // Touche ESC pour quitter
        exit(0);
    else
        move_player(keycode, data );
    return (0);
}

