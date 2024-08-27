#include "../cub3d.h"

void protected_ppx(mlx_image_t *img, int x, int y, int color)
{
    if (x <= WIDTH && x >= 0 && y >= 0 && y <= HEIGHT)
        mlx_put_pixel(img, x, y, color);
}
void protected_mppx(mlx_image_t *img, int x, int y, int color)
{
    if (x <= 200 && x >= 0 && y >= 0 && y <= 200)
        mlx_put_pixel(img, x, y, color);
}

void draw_circle(mlx_image_t *img)
{
    int x, y;
    int radius = 4;
    int radius_squared = radius * radius;

    x = 100 - radius;
    while (x <= 100 + radius)
    {
        y = 100 - radius;
        while (y <= 100 + radius)
        {
            int dx = x - 100;
            int dy = y - 100;
            if (dx * dx + dy * dy <= radius_squared)
            {
                if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
                {
                    protected_ppx(img, x, y, get_rgba(255, 0, 0, 255));
                }
            }
            y++;
        }
        x++;
    }
}

void draw_view(t_data *data)
{
    double start_angle;
    double end_angle;
    int r;

    start_angle = normalize_angle(data->player.rotation_angle - (M_PI / 6));
    end_angle =  start_angle + (M_PI / 3);

    while (start_angle <= end_angle) 
    {
        r = 5;
        while (r <= 15)
        {
            protected_mppx(data->minimap.minimap_img, 100 + (r * cos(start_angle)), 100 + (r * sin(start_angle)), get_rgba(169, 169, 169, 255));
            r++;
        }
       start_angle += 0.01;
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
