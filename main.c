#include "cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void clear_minimap(mlx_image_t *img, int color)
{
	int x;
	int y;

	y = 0;
	while (y < 200)
	{
		x = 0;
		while (x < 200)
		{
			protected_mppx(img, x, y, color);
			x++;
		}
		y++;
	}
}

void mini_map(t_data *data)
{
	int i, j;
	char map_char;
	int color;

	if (data->minimap.x_p >= 0 && data->minimap.y_p >= 0 && data->minimap.x_p < data->map->map_width * MINI_TILE &&
		data->minimap.y_p < data->map->map_height * MINI_TILE)
	{
		i = floor(data->minimap.y_p / MINI_TILE);
		j = floor(data->minimap.x_p / MINI_TILE);

		if (i < data->map->map_height && j < data->map->map_width)
		{
			map_char = data->map->map_tiles[i][j];
			color = 0;
			if (map_char == '1')
				color = get_rgba(255, 255, 255, 255);
			else
				color = get_rgba(10, 10, 10, 0);
			protected_mppx(data->minimap.minimap_img, data->minimap.x, data->minimap.y, color);
		}
	}
}

void draw_map(t_data *data)
{
	int minimap_size;

	minimap_size = 200;
	clear_minimap(data->minimap.minimap_img, get_rgba(0, 0, 0, 255));
	data->minimap.y = 0;
	data->minimap.y_p = ((data->player.y * MINI_TILE) / TILE_SIZE) - minimap_size / 2;
	while (data->minimap.y < minimap_size)
	{
		data->minimap.x = 0;
		data->minimap.x_p = ((data->player.x * MINI_TILE) / TILE_SIZE) - minimap_size / 2;
		while (data->minimap.x < minimap_size)
		{
			protected_mppx(data->minimap.minimap_img, data->minimap.x, data->minimap.y, get_rgba(10, 10, 10, 0));
			mini_map(data);
			data->minimap.x++;
			data->minimap.x_p++;
		}
		data->minimap.y++;
		data->minimap.y_p++;
	}
	draw_circle(data->minimap.minimap_img);
	draw_view(data);
}

void ft_mouse(double x, double y, void *param)
{
	t_data *data;
	double mouse_distance;
	(void)y;

	data = (t_data *)param;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (data->mouse_x != -1)
		{
			mouse_distance = x - data->mouse_x;
			data->player.rotation_angle += mouse_distance * 0.01;
			data->player.rotation_angle = normalize_angle(data->player.rotation_angle);
		}
		data->mouse_x = x;
	}
}

int main(int ac, char **av)
{
	t_data *data;

	if (ac != 2)
		return (ft_putstr_fd("Eroor\nWrong number of arguments\n", 2), ERROR);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error\nmalloc\n", 2), ERROR);
	data->addr = NULL;
	data->map = ft_calloc_ac(&data->addr, 1, sizeof(t_map));
	if (!data->map)
		return (free(data), ft_putstr_fd("Error\nmalloc\n", 2), ERROR);
	if (ft_parsing(av[1], data) == ERROR)
		return (free(data), printf("parsing failed\n"), ERROR);
	data->player.x = data->map->player_x * TILE_SIZE + TILE_SIZE / 2;
	data->player.y = data->map->player_y * TILE_SIZE + TILE_SIZE / 2;
	data->player.turn_direction = 1;
	data->player.walk_direction = 0;
	data->player.side_walk = 0;
	data->mouse_x = -1;
	data->player.close_to_wall = 0;
	if (data->map->player_direction == 'N')
		data->player.rotation_angle = 3 * M_PI / 2;
	else if (data->map->player_direction == 'S')
		data->player.rotation_angle = M_PI / 2;
	else if (data->map->player_direction == 'E')
		data->player.rotation_angle = 0;
	else if (data->map->player_direction == 'W')
		data->player.rotation_angle = M_PI;
	if (!get_textures(data))
		return (free(data), printf("parsing failed\n"), ERROR);

	// TODO protect MLX utils if each one fails
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, data->img, 0, 0);

	data->minimap.minimap_img = mlx_new_image(data->mlx, 200, 200);
	if (!(data->minimap.minimap_img))
		return (EXIT_FAILURE);
	if (mlx_image_to_window(data->mlx, data->minimap.minimap_img, 0, 0) == -1)
		return (EXIT_FAILURE);
	mlx_cursor_hook(data->mlx, &ft_mouse, data);
	mlx_loop_hook(data->mlx, &key_event_handler, data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);

	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	ft_addrclear(&data->addr, free);
	return (EXIT_SUCCESS);
}
