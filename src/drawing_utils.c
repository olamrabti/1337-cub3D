#include "../cub3d.h"

void draw_rect(mlx_image_t *img, int x , int y, int color)
{
    int tmp_x;
    int tmp_y;

    tmp_x = x ;
    tmp_y = y ;
    
    // printf("[x: %d, y: %d]\n", tmp_x, tmp_y);
    while (tmp_x <= x + SIZE) 
    {
        tmp_y = y;
        while (tmp_y <= y + SIZE) 
        {
            if (color == 1 && (tmp_y % SIZE) && (tmp_x % SIZE))
                mlx_put_pixel(img , tmp_x , tmp_y , get_rgba(255,255,255,255));
            else
                mlx_put_pixel(img, tmp_x , tmp_y , get_rgba(0, 0 ,0 ,255));
            tmp_y++;
        }
        tmp_x++;
    }
}


void draw_circle(mlx_image_t *img, int x_center, int y_center)
{
    int radius = 8;
    int x, y;

   	for (y = 0; y <= radius; y++)
	{
		for (x = 0; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
			{
				mlx_put_pixel(img, x_center + x, y_center + y, get_rgba(255, 0, 0, 255));
				mlx_put_pixel(img, x_center - x, y_center + y, get_rgba(255, 0, 0, 255));
				mlx_put_pixel(img, x_center + x, y_center - y, get_rgba(255, 0, 0, 255));
				mlx_put_pixel(img, x_center - x, y_center - y, get_rgba(255, 0, 0, 255));
			}
		}
	}
}
