#include "../cub3d.h"

void texture_ppx(t_data *data, double x, double y, t_ray *ray, double wall_height)
{
    unsigned int rel_x, rel_y;
    int color, idx;

    if (ray->direction == NORTH || ray->direction == SOUTH)
        rel_x = (fmod(ray->end_x, TILE_SIZE) / TILE_SIZE) * data->tx[ray->direction]->width;
    else
        rel_x = (fmod(ray->end_y, TILE_SIZE) / TILE_SIZE) * data->tx[ray->direction]->width;

    rel_y = ((y - (HEIGHT / 2) + (wall_height / 2)) / wall_height) * data->tx[ray->direction]->height;

    // Ensure the texture coordinates are within bounds
    if (rel_x >= data->tx[ray->direction]->width || rel_y >= data->tx[ray->direction]->height)
        return;

    idx = (rel_y * data->tx[ray->direction]->width + rel_x) * data->tx[ray->direction]->bytes_per_pixel;
    color = get_rgba(
        data->tx[ray->direction]->pixels[idx],
        data->tx[ray->direction]->pixels[idx + 1],
        data->tx[ray->direction]->pixels[idx + 2],
        data->tx[ray->direction]->pixels[idx + 3]);

    if (x < WIDTH && x >= 0 && y >= 0 && y < HEIGHT)
        protected_ppx(data->img, x, y, color);
}

void render_sky(t_data *data)
{
    unsigned int rel_x, rel_y;
    int color, idx;

    for (int y = 0; y < HEIGHT / 2; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            rel_x = ((double)x / WIDTH) * data->tx[4]->width;
            rel_y = ((double)y / (HEIGHT / 2)) * data->tx[4]->height;

            if (rel_x >= data->tx[4]->width || rel_y >= data->tx[4]->height)
                continue;

            idx = (rel_y * data->tx[4]->width + rel_x) * data->tx[4]->bytes_per_pixel;
            color = get_rgba(
                data->tx[4]->pixels[idx],
                data->tx[4]->pixels[idx + 1],
                data->tx[4]->pixels[idx + 2],
                data->tx[4]->pixels[idx + 3]);

            protected_ppx(data->img, x, y, color);
        }
    }
}

void render_land(t_data *data)
{
    for (int y = HEIGHT / 2; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int color = get_rgba(169, 161, 140, 255);

            // Render the pixel to the image
            if (x < WIDTH && x >= 0 && y >= 0 && y < HEIGHT)
                protected_ppx(data->img, x, y, color);
        }
    }
}

void render_tex_col(t_data *data, t_ray *ray, int x)
{
    double wall_height = (HEIGHT / ray->distance) * 16; // scale factor
    double wall_top = (HEIGHT / 2) - (wall_height / 2);
    double wall_bottom = wall_top + wall_height;

    // Render the wall texture column
    for (int y = wall_top; y < wall_bottom; y++)
    {
        texture_ppx(data, x, y, ray, wall_height);
    }
}

// Main rendering function
void render_frame(t_data *data)
{
    // Render the sky texture
    render_sky(data);

    render_land(data);
    // Render each column of the screen based on the raycasting results
    for (int x = 0; x < WIDTH; x++)
    {
        render_tex_col(data, &data->player.rays[x], x);
    }
}
