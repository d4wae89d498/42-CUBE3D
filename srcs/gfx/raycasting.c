#include "cube3d.h"
#include <math.h>

static void draw_line(int x, double wall_height, t_game_data *data , double wall_x, int texture_index)
{
    int start = (HEIGHT - wall_height) / 2;
    int end = start + wall_height;
    int y = 0;

    while (y < start)
    {
        ft_mlx_pixel(data->img, x, y, data->sky_color);
        y++;
    }
    while (y < end && y < HEIGHT)
    {
         // Calculate the vertical texture coordinate
        double wall_tex_pos = (y - start) / wall_height;
        // Get the texture color at the corresponding wall position
        unsigned int tex_color = get_texture_color(&data->textures[texture_index], wall_x, wall_tex_pos);
        ft_mlx_pixel(data->img, x, y, tex_color);
        y++;
    }
    while (y < HEIGHT)
    {
        ft_mlx_pixel(data->img, x, y, data->floor_color); 
        y++;
    }
}


void raycasting(t_game_data *data )
{
    int x;
    t_ray ray;
    double wall_height;

    x = 0;
    while (x < WIDTH)
    {
        ray.camera_x = 2 * x / (double)WIDTH - 1;
        ray.dir_x = data->player.dir_x + data->player.plane_x * ray.camera_x;
        ray.dir_y = data->player.dir_y + data->player.plane_y * ray.camera_x;

        ray.map_x = (int)data->player.x;
        ray.map_y = (int)data->player.y;


        ray.delta_dist_x = fabs(1 / ray.dir_x);
        ray.delta_dist_y = fabs(1 / ray.dir_y);

        ray.hit = 0;

        if (ray.dir_x < 0)
        {
            ray.step_x = -1;
            ray.side_dist_x = (data->player.x - ray.map_x) * ray.delta_dist_x;
        }
        else
        {
            ray.step_x = 1;
            ray.side_dist_x = (ray.map_x + 1.0 - data->player.x) * ray.delta_dist_x;
        }

        if (ray.dir_y < 0)
        {
            ray.step_y = -1;
            ray.side_dist_y = (data->player.y - ray.map_y) * ray.delta_dist_y;
        }
        else
        {
            ray.step_y = 1;
            ray.side_dist_y = (ray.map_y + 1.0 - data->player.y) * ray.delta_dist_y;
        }

        while (ray.hit == 0)
        {
   
            if (ray.side_dist_x < ray.side_dist_y)
            {
                ray.side_dist_x += ray.delta_dist_x;
                ray.map_x += ray.step_x;
                ray.side = 0;
            }
            else
            {
                ray.side_dist_y += ray.delta_dist_y;
                ray.map_y += ray.step_y;
                ray.side = 1;
            }

            
            if (data->map[ray.map_y][ray.map_x] == '1')
                ray.hit = 1;
            
        }

        if (ray.side == 0)
            ray.perp_wall_dist = (ray.map_x - data->player.x + (1 - ray.step_x) / 2) / ray.dir_x;
        else
            ray.perp_wall_dist = (ray.map_y - data->player.y + (1 - ray.step_y) / 2) / ray.dir_y;

        wall_height = HEIGHT / (ray.perp_wall_dist * cos(FOV_ANGLE / 2)) * 0.5;


        double wall_x; // where exactly the wall was hit

        if (ray.side == 0)
            wall_x = data->player.y + ray.perp_wall_dist * ray.dir_y;
        else
            wall_x = data->player.x + ray.perp_wall_dist * ray.dir_x;

        // Choose the texture index based on the wall's direction
         int texture_index;
        if (ray.side == 0 && ray.dir_x > 0)
            texture_index = NORTH - 1;
        else if (ray.side == 0 && ray.dir_x < 0)
            texture_index = SOUTH - 1;
        else if (ray.side == 1 && ray.dir_y > 0)
            texture_index = EAST - 1;
        else
            texture_index = WEST - 1;

        draw_line(x, wall_height, data , wall_x, texture_index);
        x++;
    }

    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}
