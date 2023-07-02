#include "cube3d.h"


#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265359
#define FOV_ANGLE (60 * (PI / 180)) // Angle de champ de vision

#define NORTH_TEXTURE_INDEX 0
#define SOUTH_TEXTURE_INDEX 1
#define EAST_TEXTURE_INDEX 2
#define WEST_TEXTURE_INDEX 3

typedef struct s_player
{
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_ray
{
    double camera_x;
    double dir_x;
    double dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int step_x;
    int step_y;
    int hit;
    int side;
} t_ray;

typedef struct s_mlx_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     width;
    int     height;
}	t_mlx_img;

typedef struct 
{
    void *mlx_ptr;
    void *win_ptr;
    t_player player;
    t_mlx_img	img;
    	t_mlx_img		textures[4];
}   game_ctx;

void	ft_mlx_pixel(t_mlx_img img, int x, int y, unsigned int color)
{
	*(unsigned int *)
		(img.addr
			+ (y * img.line_length + x * (img.bits_per_pixel / 8)))
		= color;
}

int map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

unsigned int get_color(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}


unsigned int get_texture_color(t_mlx_img *texture, double u, double v)
{
    int tex_x;
    int tex_y;

    tex_x = u * texture->width;
    tex_y = v * texture->height;
    return *(unsigned int *)(texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8)));
}


void draw_line(int x, double wall_height, game_ctx *ctx, double wall_x, int texture_index)
{
    int start = (HEIGHT - wall_height) / 2;
    int end = start + wall_height;
    int y = 0;

    while (y < start)
    {
        ft_mlx_pixel(ctx->img, x, y, get_color(0, 0, 255)); // Couleur du ciel (bleu)
        y++;
    }
    while (y < end && y < HEIGHT)
    {
         // Calculate the vertical texture coordinate
        double wall_tex_pos = (y - start) / wall_height;
        // Get the texture color at the corresponding wall position
        unsigned int tex_color = get_texture_color(&ctx->textures[texture_index], wall_x, wall_tex_pos);
        ft_mlx_pixel(ctx->img, x, y, tex_color);
        y++;
    }
    while (y < HEIGHT)
    {
        ft_mlx_pixel(ctx->img, x, y, get_color(255, 0, 0)); // Couleur du sol (rouge)
        y++;
    }
}


void raycasting(game_ctx *ctx)
{
    int x;
    t_ray ray;
    double wall_height;

    x = 0;
    while (x < WIDTH)
    {
        ray.camera_x = 2 * x / (double)WIDTH - 1;
        ray.dir_x = ctx->player.dir_x + ctx->player.plane_x * ray.camera_x;
        ray.dir_y = ctx->player.dir_y + ctx->player.plane_y * ray.camera_x;

        ray.map_x = (int)ctx->player.x;
        ray.map_y = (int)ctx->player.y;

        ray.delta_dist_x = fabs(1 / ray.dir_x);
        ray.delta_dist_y = fabs(1 / ray.dir_y);

        ray.hit = 0;

        if (ray.dir_x < 0)
        {
            ray.step_x = -1;
            ray.side_dist_x = (ctx->player.x - ray.map_x) * ray.delta_dist_x;
        }
        else
        {
            ray.step_x = 1;
            ray.side_dist_x = (ray.map_x + 1.0 - ctx->player.x) * ray.delta_dist_x;
        }

        if (ray.dir_y < 0)
        {
            ray.step_y = -1;
            ray.side_dist_y = (ctx->player.y - ray.map_y) * ray.delta_dist_y;
        }
        else
        {
            ray.step_y = 1;
            ray.side_dist_y = (ray.map_y + 1.0 - ctx->player.y) * ray.delta_dist_y;
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

            if (map[ray.map_y][ray.map_x] == 1)
                ray.hit = 1;
            
        }

        if (ray.side == 0)
            ray.perp_wall_dist = (ray.map_x - ctx->player.x + (1 - ray.step_x) / 2) / ray.dir_x;
        else
            ray.perp_wall_dist = (ray.map_y - ctx->player.y + (1 - ray.step_y) / 2) / ray.dir_y;

        wall_height = HEIGHT / (ray.perp_wall_dist * cos(FOV_ANGLE / 2)) * 0.5;


        double wall_x; // where exactly the wall was hit

        if (ray.side == 0)
            wall_x = ctx->player.y + ray.perp_wall_dist * ray.dir_y;
        else
            wall_x = ctx->player.x + ray.perp_wall_dist * ray.dir_x;

        // Choose the texture index based on the wall's direction
         int texture_index;
        if (ray.side == 0 && ray.dir_x > 0)
            texture_index = NORTH_TEXTURE_INDEX;
        else if (ray.side == 0 && ray.dir_x < 0)
            texture_index = SOUTH_TEXTURE_INDEX;
        else if (ray.side == 1 && ray.dir_y > 0)
            texture_index = EAST_TEXTURE_INDEX;
        else
            texture_index = WEST_TEXTURE_INDEX;

        draw_line(x, wall_height, ctx, wall_x, texture_index);
        x++;
    }

    mlx_clear_window(ctx->mlx_ptr, ctx->win_ptr);
    mlx_put_image_to_window(ctx->mlx_ptr, ctx->win_ptr, ctx->img.img, 0, 0);
}

void move_player(int keycode, game_ctx *ctx)
{
    double move_speed;
    double rot_speed;

    move_speed = 0.05;
    rot_speed = 0.05;

    if (keycode == 119) // W
    {
        if (map[(int)(ctx->player.y + ctx->player.dir_y * move_speed)][(int)ctx->player.x] == 0)
            ctx->player.y += ctx->player.dir_y * move_speed;
        if (map[(int)ctx->player.y][(int)(ctx->player.x + ctx->player.dir_x * move_speed)] == 0)
            ctx->player.x += ctx->player.dir_x * move_speed;
    }
    else if (keycode == 115) // S
    {
        if (map[(int)(ctx->player.y - ctx->player.dir_y * move_speed)][(int)ctx->player.x] == 0)
            ctx->player.y -= ctx->player.dir_y * move_speed;
        if (map[(int)ctx->player.y][(int)(ctx->player.x - ctx->player.dir_x * move_speed)] == 0)
            ctx->player.x -= ctx->player.dir_x * move_speed;
    }
    else if (keycode == 100) // D
    {
        double old_dir_x = ctx->player.dir_x;
        ctx->player.dir_x = ctx->player.dir_x * cos(-rot_speed) - ctx->player.dir_y * sin(-rot_speed);
        ctx->player.dir_y = old_dir_x * sin(-rot_speed) + ctx->player.dir_y * cos(-rot_speed);
        double old_plane_x = ctx->player.plane_x;
        ctx->player.plane_x = ctx->player.plane_x * cos(-rot_speed) - ctx->player.plane_y * sin(-rot_speed);
        ctx->player.plane_y = old_plane_x * sin(-rot_speed) + ctx->player.plane_y * cos(-rot_speed);
    }
    else if (keycode == 97) // A
    {
        double old_dir_x = ctx->player.dir_x;
        ctx->player.dir_x = ctx->player.dir_x * cos(rot_speed) - ctx->player.dir_y * sin(rot_speed);
        ctx->player.dir_y = old_dir_x * sin(rot_speed) + ctx->player.dir_y * cos(rot_speed);
        double old_plane_x = ctx->player.plane_x;
        ctx->player.plane_x = ctx->player.plane_x * cos(rot_speed) - ctx->player.plane_y * sin(rot_speed);
        ctx->player.plane_y = old_plane_x * sin(rot_speed) + ctx->player.plane_y * cos(rot_speed);
    }
    printf("KEY PRESS!\n");
    raycasting(ctx);
}

int key_press(int keycode, void *param)
{
    game_ctx *ctx;

    ctx = (game_ctx *)param;
    printf("keycode ; %i\n", keycode);
    if (keycode == 65307) // Touche ESC pour quitter
        exit(0);
    else
        move_player(keycode, ctx);
    return (0);
}



/*
int render_next_frame(g_game_ctx *ctx)
{
   aycasting(&(ctx->player), ctx->mlx_ptr, ctx->win_ptr);
    return 0;
}*/

#define north_path "assets/north.xpm"
#define south_path "assets/south.xpm"
#define east_path "assets/east.xpm"
#define west_path "assets/west.xpm"


int main(int ac, char **av)
{

    t_data      data;
    t_err       ret;

    if ((ret = ft_init(&data)) != OK)
        return (ft_error(ret, &data));
    if ((ret = ft_parse(ac, av, &data)) != OK)
        return (ft_error(ret, &data));
    game_ctx ctx; 

    ctx.player.x = 1.5;
    ctx.player.y = 1.5;
    ctx.player.dir_x = 0.0;
    ctx.player.dir_y = 1.0;
    ctx.player.plane_x = 0.66;
    ctx.player.plane_y = 0.0;

    ctx.mlx_ptr = mlx_init();
    ctx.win_ptr = mlx_new_window(ctx.mlx_ptr, WIDTH, HEIGHT, "cube3d");


		ctx.img.img = mlx_new_image(ctx.mlx_ptr, WIDTH, HEIGHT);
		ctx.img.addr = mlx_get_data_addr(ctx.img.img, &(ctx.img.bits_per_pixel),
				&(ctx.img.line_length),
				&(ctx.img.endian));

    mlx_hook(ctx.win_ptr, 2, 1L << 0, key_press, &ctx);


    ctx.textures[0].img = mlx_xpm_file_to_image(ctx.mlx_ptr, north_path, &(ctx.textures[0].width), &(ctx.textures[0].height));
	ctx.textures[1].img = mlx_xpm_file_to_image(ctx.mlx_ptr, south_path, &(ctx.textures[0].width), &(ctx.textures[0].height));
	ctx.textures[2].img = mlx_xpm_file_to_image(ctx.mlx_ptr, east_path, &(ctx.textures[0].width), &(ctx.textures[0].height));
	ctx.textures[3].img = mlx_xpm_file_to_image(ctx.mlx_ptr, west_path, &(ctx.textures[0].width), &(ctx.textures[0].height));

	for (int i = 0; i < 4; i++)
	{
		ctx.textures[i].addr = mlx_get_data_addr(ctx.textures[i].img, &(ctx.textures[i].bits_per_pixel), &(ctx.textures[i].line_length), &(ctx.textures[i].endian));
        ctx.textures[i].width = 512;
        ctx.textures[i].height = 512;
    }

    raycasting(&ctx);
	//mlx_loop_hook(ctx.mlx_ptr, render_next_frame, &ctx);
    
    mlx_loop(ctx.mlx_ptr);
    
    return (0);
}
