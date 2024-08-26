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
    int x, y;
    int radius = 4;
    int radius_squared = radius * radius;

    x = x_center - radius;
    // Iterate over the square bounding box of the circle
    while (x <= x_center + radius)
    {
        y = y_center - radius;
        while (y <= y_center + radius)
        {
            // Check if the point is inside the circle
            int dx = x - x_center;
            int dy = y - y_center;
            if (dx * dx + dy * dy <= radius_squared)
            {
                // Check if the point is within the image boundaries
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

void line(mlx_image_t *img, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        protected_ppx(img, x1, y1, color); // Set the pixel at the current position

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

// void draw_view(t_data *data)
// {
//     int apex_x = 100;                                              // The x-coordinate of the triangle's apex
//     int apex_y = 100;                                              // The y-coordinate of the triangle's apex
//     int radius = 50;                                               // Length of the triangle's height (adjust as needed)
//     double start_angle = data->player.rotation_angle - (M_PI / 6); // 30 degrees to the left
//     double end_angle = data->player.rotation_angle + (M_PI / 6);   // 30 degrees to the right

//     // Calculate the two base points of the triangle
//     int base_left_x = apex_x + radius * cos(start_angle);
//     int base_left_y = apex_y + radius * sin(start_angle);
//     int base_right_x = apex_x + radius * cos(end_angle);
//     int base_right_y = apex_y + radius * sin(end_angle);

//     // Draw the triangle using the three points: apex, base_left, and base_right
//     line(data->minimap.minimap_img, apex_x, apex_y, base_left_x, base_left_y, get_rgba(0, 255, 0, 255));
//     line(data->minimap.minimap_img, apex_x, apex_y, base_right_x, base_right_y, get_rgba(0, 255, 0, 255));
//     line(data->minimap.minimap_img, base_left_x, base_left_y, base_right_x, base_right_y, get_rgba(0, 255, 0, 255));


// }

double normalize_angle(double angle)
{
    double normalized;

    normalized = fmod(angle, 2 * M_PI);
    if (normalized < 0.0)
        normalized += 2 * M_PI;
    return normalized;
}
