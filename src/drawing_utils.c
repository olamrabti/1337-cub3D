#include "../cub3d.h"

void protected_ppx(mlx_image_t *img, int x, int y, int color)
{
    if (x < WIDTH && x > 0 && y > 0 && y < HEIGHT)
        mlx_put_pixel(img, x, y, color);

}
void draw_rect(mlx_image_t *img, int x, int y, int color)
{
    int tmp_x;
    int tmp_y;

    tmp_x = x;
    tmp_y = y;

    // printf("[x: %d, y: %d]\n", tmp_x, tmp_y);
    while (tmp_x <= x + SIZE)
    {
        tmp_y = y;
        while (tmp_y <= y + SIZE)
        {
            if (color == 1 && (tmp_y % SIZE) && (tmp_x % SIZE))
                protected_ppx(img, tmp_x, tmp_y, get_rgba(255, 255, 255, 255));
            else
                protected_ppx(img, tmp_x, tmp_y, get_rgba(0, 0, 0, 255));
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
                protected_ppx(img, x_center + x, y_center + y, get_rgba(255, 0, 0, 255));
                protected_ppx(img, x_center - x, y_center + y, get_rgba(255, 0, 0, 255));
                protected_ppx(img, x_center + x, y_center - y, get_rgba(255, 0, 0, 255));
                protected_ppx(img, x_center - x, y_center - y, get_rgba(255, 0, 0, 255));
            }
        }
    }
}

void draw_line(t_data data, int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while(1)
    {
        if (is_wall(data, x1, y1))
            break ;
        protected_ppx(data.img, x1 , y1, get_rgba(255, 0, 0, 255));
        if (x1 == x2 && y1 == y2)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
}

int is_wall(t_data data, int x, int y)
{

    // printf("map : %c", data.map[y / SIZE][x / SIZE]);
    // printf("x /size : %d, y / size : %d\n", x /SIZE, y/SIZE );
    if(y < 0 || x < 0 || (y / SIZE) >= data.lines || (x / SIZE) >= ft_strlen(data.map[y / SIZE]))
        return 0;    
    if (data.map[y / SIZE][x / SIZE] == '1')
        return 1;
    return 0;
}

void draw_rays(t_data data)
{
    double angle;

    angle = data.player.rotation_angle - (M_PI / 6);
    while (angle <= data.player.rotation_angle + (M_PI / 6))
    {
	    draw_line(data, data.player.x, data.player.y, data.player.x + cos(angle) * WIDTH, data.player.y + sin(angle) * HEIGHT);  
        angle += 0.01;
    }
}