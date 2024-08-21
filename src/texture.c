#include "../cub3d.h"

void get_textures(t_data *data)
{
    data->tx = mlx_load_png(data->map->no_texture_path);
    if (!data->tx)
        printf("Texture Loading Error\n");
    printf("image height : %d\n", data->tx->height);
    printf("image width : %d\n", data->tx->width);
    printf("100 pixel : %d\n", data->tx->pixels[230]);
    printf("101 pixel : %d\n", data->tx->pixels[231]);
    printf("102 pixel : %d\n", data->tx->pixels[232]);
    printf("103 pixel : %d\n", data->tx->pixels[233]);
}
