#include "../cub3d.h"

int get_textures(t_data *data)
{
    data->tx = ft_calloc_ac(&data->addr, 6, sizeof(mlx_texture_t));
    if (!data->tx)
        return 0;
    data->tx[0] = mlx_load_png(data->map->no_texture_path);
    data->tx[1] = mlx_load_png(data->map->so_texture_path);
    data->tx[2] = mlx_load_png(data->map->we_texture_path);
    data->tx[3] = mlx_load_png(data->map->ea_texture_path);
    data->tx[4] = mlx_load_png("./textures/skyblue.png");
    data->tx[5] = mlx_load_png("./textures/land.png");
    if (!data->tx[0] || !data->tx[1] || !data->tx[2] || !data->tx[3])
       return ft_putstr_fd("Error\nTexture Loading Error\n", 2), 0;
    return 1;
}
