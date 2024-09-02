/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 04:58:43 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/02 11:13:44 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	protected_ppx(mlx_image_t *img, int x, int y, int color)
{
	if (x <= WIDTH && x >= 0 && y >= 0 && y <= HEIGHT)
		mlx_put_pixel(img, x, y, color);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	is_wall(t_data *data, double x, double y)
{
	double	map_x;
	double	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (map_x > 0 && map_x < data->map->map_width && map_y > 0 \
		&& map_y < (data->map->map_height))
	{
		if (data->map->map_tiles[(int)map_y][(int)map_x] != '0')
			return (1);
		return (0);
	}
	return (1);
}

void	clear_screen(mlx_image_t *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			protected_ppx(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_data *data)
{
	int	minimap_size;

	minimap_size = 200;
	clear_minimap(data->minimap.minimap_img, get_rgba(0, 0, 0, 255));
	data->minimap.y = 0;
	data->minimap.y_p = ((data->player.y * MINI_TILE) / TILE_SIZE) \
		- minimap_size / 2;
	while (data->minimap.y < minimap_size)
	{
		data->minimap.x = 0;
		data->minimap.x_p = ((data->player.x * MINI_TILE) / TILE_SIZE) \
			- minimap_size / 2;
		while (data->minimap.x < minimap_size)
		{
			protected_mppx(data->minimap.minimap_img, data->minimap.x, \
				data->minimap.y, get_rgba(10, 10, 10, 100));
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
