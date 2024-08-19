#include "../cub3d.h"

void protected_ppx(mlx_image_t *img, int x, int y, int color)
{
    if (x < WIDTH && x > 0 && y > 0 && y < HEIGHT)
        mlx_put_pixel(img, x, y, color);
}
void draw_rect(t_data *data, int x, int y, int color)
{
    int tmp_x;
    int tmp_y;

    tmp_x = x;
    tmp_y = y;

    // printf("[x: %d, y: %d]\n", tmp_x, tmp_y);
    while (tmp_x <= x + data->map->tile_size)
    {
        tmp_y = y;
        while (tmp_y <= y + data->map->tile_size)
        {
            if (color == 1 && (tmp_y % data->map->tile_size) && (tmp_x % data->map->tile_size))
                protected_ppx(data->img, tmp_x, tmp_y, get_rgba(255, 255, 255, 10));
            else
                protected_ppx(data->img, tmp_x, tmp_y, get_rgba(0, 0, 0, 10));
            tmp_y++;
        }
        tmp_x++;
    }
}

void draw_circle(mlx_image_t *img, int x_center, int y_center)
{
    int radius = 2;
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

double draw_line(t_data *data, double x1, double y1, double x2, double y2, int color)
{
    double dx = fabs(x2 - x1);
    double dy = fabs(y2 - y1);
    double sx = x1 < x2 ? 1 : -1;
    double sy = y1 < y2 ? 1 : -1;
    double err = (dx > dy ? dx : -dy) / 2;
    double e2;
    int i;
    i = 0;
    while (1)
    {
        if (!is_wall(data, x1, y1))
        {
            if (color == 1)
                protected_ppx(data->img, (int)x1, (int)y1, get_rgba(255, 0, 0, 10));
            if (color == 2)
                protected_ppx(data->img, (int)x1, (int)y1, get_rgba(0, 255, 0, 10));
        }
        else
            break;
        i++;
        if (x1 == x2 && y1 == y2)
            return get_distance(data, x1, y1);
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
    return get_distance(data, x1, y1);
}

double normalize_angle(double angle)
{
    double normalized;
    
    normalized = fmod(angle, 2 * M_PI);
    if (normalized < 0.0)
        normalized += 2 * M_PI;
    return normalized;
}

