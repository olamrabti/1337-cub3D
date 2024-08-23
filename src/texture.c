#include "../cub3d.h"

void get_textures(t_data *data)
{
    int i = 0;
    int j = 0;

    data->tx = mlx_load_png(data->map->no_texture_path);
    if (!data->tx)
        printf("Texture Loading Error\n");
    // while(i < data->tx->height * data->tx->width)
    // {
    //     if (!(i % data->tx->width) && j++)
    //         printf("pixel[%d] : %d\n", i, data->tx->pixels[i]);
    //     i++;
    // }
    printf("image width : %d\n", data->tx->width);
    // printf("j: %d\n", j);
    printf("image height : %d\n", data->tx->height);
}
