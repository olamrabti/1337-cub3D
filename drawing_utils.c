#include "cub3d.h"

void draw_rect(mlx_image_t *img, int x , int y, int color)
{
    int tmp_x;
    int tmp_y;

    tmp_x = x ;
    tmp_y = y ;
    
    while (tmp_x < WIDTH) 
    {
        tmp_y = y;
        while (tmp_y <= HEIGHT) 
        {
            // printf("[x: %d, y: %d]\n", tmp_x, tmp_y);
            if (color == 1 && tmp_x % SIZE && tmp_y % SIZE)
                mlx_put_pixel(img , tmp_x , tmp_y , WHITE);
            else
                mlx_put_pixel(img, tmp_x , tmp_y , BLACK);
            tmp_y++;
        }
        tmp_x++;
    }
}