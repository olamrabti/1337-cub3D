/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 04:58:43 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/06 10:46:44 by olamrabt         ###   ########.fr       */
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

int	is_wall_p(t_data *data, double p_x, double p_y)
{
	double	x;
	double	y;
	int		radius;

	radius = 4;
	x = p_x - radius;
	while (x <= p_x + radius)
	{
		y = p_y - radius;
		while (y <= p_y + radius)
		{
			if (pow(x - p_x, 2) + pow(y - p_y, 2) <= pow(radius, 2))
				if (is_wall(data, x, y))
					return (1);
			y++;
		}
		x++;
	}
	return (0);
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
