#include "../cub3d.h"

void texture_ppx(t_data *data, double x, double y, t_ray *ray)
{
    int rel_x;
    int rel_y;
    int color;
    int index;

    if (ray->direction == HORI)
        rel_x = (fmod(ray->end_x, data->map->tile_size)  / data->map->tile_size) * data->tx->width ;
    else
        rel_x = (fmod(ray->end_y, data->map->tile_size)  / data->map->tile_size) * data->tx->width ;
    
    rel_y = y  * data->tx->height / HEIGHT;
    if (rel_x < 0 || rel_x  >= data->tx->width || rel_y < 0 || rel_y >= data->tx->height)
        return;
    index = (rel_y * data->tx->width + rel_x) * data->tx->bytes_per_pixel;
    color = get_rgba(data->tx->pixels[index], data->tx->pixels[index + 1], data->tx->pixels[index + 2], data->tx->pixels[index + 3]);
    if (x < WIDTH && x >= 0 && y >= 0 && y < HEIGHT)
        mlx_put_pixel(data->img, x, y, color);
}



void render_tex_col(t_data *data, t_ray *ray, int x)
{
    double wall_height;
    double wall_top;
    double wall_bottom;
    double scale;

    scale = 12;
    wall_height = ((HEIGHT / ray->distance) * scale);
    wall_top = (HEIGHT / 2) - (wall_height / 2);
    wall_bottom = wall_top + wall_height;

    // printf("direction: %d\n", wall_height);
    while (wall_top < wall_bottom)
    {
        texture_ppx(data, x, wall_top, ray);
        wall_top++;
    }
}

// void render_wall(t_data *data, double distance, int ray_index, int direction )
// {
//     double wall_height;
//     double wall_top;
//     double wall_bottom;
//     double scale;

//     scale = 16;
//     wall_height = ((HEIGHT / distance) * scale);
//     // wall_height = ((int)(HEIGHT / distance));
//     wall_top = (HEIGHT / 2) - (wall_height / 2);
//     wall_bottom = wall_top + wall_height;

//     // printf("wall_top : %d\n", wall_top);
//     while (wall_top < wall_bottom)
//     {
//         wall_top++;
//         if (direction == VERTI)
//             protected_ppx(data->img, ray_index, wall_top, get_rgba(72, 34, 9, 255));
//         else
//             protected_ppx(data->img, ray_index, wall_top, get_rgba(91, 43, 23, 255));
//     }
// }
