/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 05:01:09 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/02 02:19:53 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_mouse(double x, double y, void *param)
{
	t_data	*data;
	double	mouse_distance;

	data = (t_data *)param;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (data->mouse_x != -1)
		{
			mouse_distance = x - data->mouse_x;
			data->player.rotation_angle += mouse_distance * 0.01;
			data->player.rotation_angle = \
				normalize_angle(data->player.rotation_angle);
		}
		data->mouse_x = x;
	}
}

int	init_player(t_data *data)
{
	data->player.x = (data->map->player_x * TILE_SIZE) + (TILE_SIZE / 2);
	data->player.y = (data->map->player_y * TILE_SIZE) + (TILE_SIZE / 2);
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
		return (ERROR);
	return (SUCCESS);
}

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D_bonus", false);
	if (!data->mlx)
		return (ERROR);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		return (ERROR);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
		return (ERROR);
	data->minimap.minimap_img = mlx_new_image(data->mlx, 200, 200);
	if (!(data->minimap.minimap_img))
		return (ERROR);
	if (mlx_image_to_window(data->mlx, data->minimap.minimap_img, 0, 0) == -1)
		return (ERROR);
	return (SUCCESS);
}

int	ft_clean_exit(t_data *data)
{
	ft_addrclear(&data->addr, free);
	free(data);
	return (ERROR);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_map	*map;
	t_addr	*addr;

	if (ac != 2)
		return (ft_putstr_fd("Error\nWrong number of arguments\n", 2), ERROR);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_putstr_fd("Error\nmalloc\n", 2), ERROR);
	addr = NULL;
	// data->map = safe_alloc(&data->addr, 1, sizeof(t_map));
	map = malloc(sizeof(t_map));
	if (!map)
		return (ft_putstr_fd("Error\nmalloc\n", 2), ft_clean_exit(data));
	map->map_tiles = NULL;
	map->no_texture_path = NULL;
	map->so_texture_path = NULL;
	map->we_texture_path = NULL;
	map->ea_texture_path = NULL;
	map->f_color = NULL;
	map->c_color = NULL;
	map->single_line_map = NULL;
	map->single_line_vars = NULL;
	map->c_rgb = NULL;
	map->f_rgb = NULL;
	map->player_direction = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->map_width = 0;
	map->map_height = 0;
	map->tile_size = 0;
	
	if (ft_parsing(av[1], &map, &addr) == ERROR)
		return (ft_clean_exit(data));
	data->map = map;
	data->addr = addr;
	if (init_player(data) != SUCCESS)
		return (ft_clean_exit(data));
	if (init_mlx(data) != SUCCESS)
		return (ft_putstr_fd("Error\n MLX initialization\n", 2), \
			ft_clean_exit(data));
	mlx_cursor_hook(data->mlx, &ft_mouse, data);
	if (!mlx_loop_hook(data->mlx, &key_event_handler, data))
		return (ft_putstr_fd("Error\n MLX initialization\n", 2), \
			ft_clean_exit(data));
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop(data->mlx);
	// delete_textures(data);
	mlx_terminate(data->mlx);
	// ft_clean_exit(data);
	// atexit(f);
	return (SUCCESS);
}
