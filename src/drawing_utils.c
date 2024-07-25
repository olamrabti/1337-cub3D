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

double get_distance(t_data data, int x_wall, int y_wall, int num_pixels)
{
    if (num_pixels < 2)
        return 0.0;
    double total_distance = 0.0;
    int dx = x_wall - data.player.x;
    int dy = y_wall - data.player.y;
    total_distance += sqrt(dx * dx + dy * dy);
    return total_distance;
}

double draw_line(t_data data, int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;
    int i;
    i = 0;
    while (1)
    {
        if (is_wall(data, x1, y1))
            return get_distance(data, x1, y1, i);
        protected_ppx(data.img, x1, y1, get_rgba(255, 0, 0, 255));
        i++;
        if (x1 == x2 && y1 == y2)
            return get_distance(data, x1, y1, i);
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
    return 0;
}

int is_wall(t_data data, int x, int y)
{

    // printf("map : %c", data.map[y / SIZE][x / SIZE]);
    // printf("x /size : %d, y / size : %d\n", x /SIZE, y/SIZE );
    if (y < 0 || x < 0 || (y / SIZE) >= data.lines || (x / SIZE) >= ft_strlen(data.map[y / SIZE]))
        return 0;
    if (data.map[y / SIZE][x / SIZE] == '1')
        return 1;
    return 0;
}

void clear_screen(mlx_image_t *img, int color)
{
    int x, y;
    for (y = 0; y < HEIGHT; ++y)
    {
        for (x = 0; x < WIDTH; ++x)
            protected_ppx(img, x, y, color);
    }
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