#include "../cub3d.h"

void draw_rect(mlx_image_t *img, int x , int y, int color)
{
    int tmp_x;
    int tmp_y;

    tmp_x = x ;
    tmp_y = y ;
    
    // printf("[x: %d, y: %d]\n", tmp_x, tmp_y);
    while (tmp_x < x + (WIDTH / 12)) 
    {
        tmp_y = y;
        while (tmp_y < y + (HEIGHT / 12)) 
        {
            if (color == 1 && tmp_x % (HEIGHT / 12) && tmp_y % (HEIGHT / 12))
                mlx_put_pixel(img , tmp_x , tmp_y , WHITE);
            else
                mlx_put_pixel(img, tmp_x , tmp_y , BLACK);
            tmp_y++;
        }
        tmp_x++;
    }
}
