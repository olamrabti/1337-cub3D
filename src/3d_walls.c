#include "../cub3d.h"

void render_wall(t_data *data, double distance, int ray_index, int direction )
{
    double wall_height;
    double wall_top;
    double wall_bottom;
    double scale;

    scale = 16;
    wall_height = ((HEIGHT / distance) * scale);
    // wall_height = ((int)(HEIGHT / distance));
    wall_top = (HEIGHT / 2) - (wall_height / 2);
    wall_bottom = wall_top + wall_height;

    // printf("wall_top : %d\n", wall_top);
    while (wall_top < wall_bottom)
    {
        wall_top++;
        if (direction == VERTI)
            protected_ppx(data->img, ray_index, wall_top, get_rgba(255, 200, 0, 255)); 
        else
            protected_ppx(data->img, ray_index, wall_top, get_rgba(30, 200, 50, 255));
    }
}

