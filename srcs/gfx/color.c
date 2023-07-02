#include "cube3d.h"

void	ft_mlx_pixel(t_mlx_img img, int x, int y, unsigned int color)
{
	*(unsigned int *)
		(img.addr
			+ (y * img.line_length + x * (img.bits_per_pixel / 8)))
		= color;
}

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
