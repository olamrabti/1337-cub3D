#include "cub3d.h"


int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	hook(void* arg)
{
	if (mlx_is_key_down((mlx_t*)arg, MLX_KEY_ESCAPE))
		mlx_close_window((mlx_t*)arg);
}

void draw_map (t_data *data)
{
	int i;
	int j;
	int x; // 
	int y; // 

	i = 0;
	x = 0;
	y = 0;
	while (i < data->lines) // 
	{
		j = 0;
		y = 0;
		while (j < ft_strlen(data->map[i])) // 
		{
			if (data->map[i][j])
				draw_rect(data->img,y, x, (int)data->map[i][j] - 48);
			else 
				draw_rect(data->img,y, x, 0);
			j++;
			y += SIZE;
		}
		i++;
		x += SIZE;
	}
}

int	main(void)
{
	t_data data;

	data.addr = NULL;
	data.player.x = WIDTH / 16;
	data.player.y = HEIGHT / 16;
	data.player.turn_direction = 1;
	data.player.walk_direction = 0;
	data.player.rotation_angle = 0;

	// TODO protect MLX utils if each one fails
	data.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	parse_map(&data, "./maps/example.map");
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	draw_map(&data);
	draw_player(data);
	mlx_loop_hook(data.mlx, &key_event_handler, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_addrclear(&data.addr, free);
	return (EXIT_SUCCESS);
}
