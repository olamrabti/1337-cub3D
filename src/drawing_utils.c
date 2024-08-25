#include "../cub3d.h"

void protected_ppx(mlx_image_t *img, int x, int y, int color)
{
    if (x <= WIDTH && x >= 0 && y >= 0 && y <= HEIGHT)
        mlx_put_pixel(img, x, y, color);
}
void draw_rect(t_data *data, int x, int y, int color)
{
    int tmp_x;
    int tmp_y;

    tmp_x = x;
    tmp_y = y;
    while (tmp_x <= x + data->map->tile_size)
    {
        tmp_y = y;
        while (tmp_y <= y + data->map->tile_size)
        {
            if (color == 1 && (tmp_y % data->map->tile_size) && (tmp_x % data->map->tile_size))
                protected_ppx(data->img, tmp_x, tmp_y, get_rgba(255, 255, 255, 30));
            else
                protected_ppx(data->img, tmp_x, tmp_y, get_rgba(0, 0, 0, 30));
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
void draw_view(t_data *data, double scale)
{
    int radius;
    double angle;
    double start_angle;
    double end_angle;
    double x, y;

    radius = TILE_SIZE / 6;
    start_angle = data->player.rotation_angle - (M_PI / 6); 
    end_angle = data->player.rotation_angle + (M_PI / 6);

    for (angle = start_angle; angle <= end_angle; angle += 0.01) 
    {
        for (int r = 0; r <= radius; r++)
        {
            x = data->player.x * scale + r * cos(angle);
            y = data->player.y * scale + r * sin(angle);
            protected_ppx(data->img, (int)x, (int)y, get_rgba(0, 255, 0, 255));
        }
    }
}


double normalize_angle(double angle)
{
    double normalized;
    
    normalized = fmod(angle, 2 * M_PI);
    if (normalized < 0.0)
        normalized += 2 * M_PI;
    return normalized;
}

