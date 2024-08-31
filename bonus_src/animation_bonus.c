#include "cub3d_bonus.h"

mlx_image_t *ft_get_frame(t_data *data)
{
    char *path;
    mlx_texture_t *texture;
    mlx_image_t *frame;

    if (data->frame)
        mlx_delete_image(data->mlx, data->frame);
    path = gc_strjoin("./animation/", gc_itoa(data->frame_num, &data->addr), &data->addr);
    path = gc_strjoin(path, ".png", &data->addr);
    texture = mlx_load_png(path);
    if (!texture)
        exit(EXIT_FAILURE);
    frame = mlx_texture_to_image(data->mlx, texture);
    mlx_delete_texture(texture);
    if (!frame)
        exit(EXIT_FAILURE);
    return (frame);
}

void ft_animation(t_data *data, int x, int y)
{
    static int i = 1;

    if (i == 24)
        i = 1;
    data->frame_num = i;
    data->frame = ft_get_frame(data);
    mlx_image_to_window(data->mlx, data->frame, x, y);
    i++;
}