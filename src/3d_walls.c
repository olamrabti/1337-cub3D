#include "../cub3d.h"

void texture_ppx(t_data *data, int x, int y, int direction)
{
    int rel_x;
    int rel_y;
    int color;
    int index;

    rel_x = data->tx->width * (x / data->map->tile_size);
    rel_y = data->tx->height * (y / data->map->tile_size);
    index = rel_y + rel_x;
    color = get_rgba(data->tx->pixels[index], data->tx->pixels[index + 1], data->tx->pixels[index + 2], data->tx->pixels[index + 3]);

    // printf("image height : %d\n", data->tx->height);
    // printf("image width : %d\n", data->tx->width);
    // printf("index : %d\n", index);
    // printf("rel_x : %d\n", rel_x);
    // printf("rel_y : %d\n", rel_y);
    // printf("x : %d\n", x);
    // printf("y : %d\n", y);
    // printf("r : %d\n", data->tx->pixels[index]);
    // printf("g : %d\n", data->tx->pixels[index + 1]);
    // printf("b : %d\n", data->tx->pixels[index + 2]);
    // printf("a : %d\n", data->tx->pixels[index + 3]);

  
    if (x < WIDTH && x > 0 && y > 0 && y < HEIGHT)
        mlx_put_pixel(data->img, x, y, color);

    // if (x < WIDTH && x > 0 && y > 0 && y < HEIGHT)
    //     mlx_put_pixel(data->img, x, y, get_rgba(75,0,10,255));
}

void render_tex_col(t_data *data, double distance, int x, int direction)
{
    double wall_height;
    double wall_top;
    double wall_bottom;
    double scale;

    scale = 16;
    wall_height = ((HEIGHT / distance) * scale);
    wall_top = (HEIGHT / 2) - (wall_height / 2);
    wall_bottom = wall_top + wall_height;

    // printf("wall_top : %d\n", wall_top);
    while (wall_top < wall_bottom)
    {
        wall_top++;
        // if (direction == VERTI)
        //     texture_ppx(data->img, x, wall_top, get_rgba(72, 34, 9, 255));
        // else
        texture_ppx(data, x, wall_top, get_rgba(91, 43, 23, 255));
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
