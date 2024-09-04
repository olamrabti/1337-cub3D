/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 05:04:28 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/04 17:56:07 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	protected_mppx(mlx_image_t *img, int x, int y, int color)
{
	if (x <= 200 && x >= 0 && y >= 0 && y <= 200)
		mlx_put_pixel(img, x, y, color);
}

void	draw_circle(mlx_image_t *img)
{
	int	x;
	int	y;
	int	radius;

	radius = 4;
	x = 100 - radius;
	while (x <= 100 + radius)
	{
		y = 100 - radius;
		while (y <= 100 + radius)
		{
			if (pow(x - 100, 2) + pow(y - 100, 2) <= pow(radius, 2))
				if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
					protected_ppx(img, x, y, get_rgba(255, 0, 0, 255));
			y++;
		}
		x++;
	}
}

void	draw_view(t_data *data)
{
	double	start_angle;
	double	end_angle;
	int		r;

	start_angle = normalize_angle(data->player.rotation_angle - (M_PI / 4));
	end_angle = start_angle + (M_PI / 2);
	while (start_angle <= end_angle)
	{
		r = 5;
		while (r <= 15)
		{
			protected_mppx(data->minimap.minimap_img, 100 + \
				(r * cos(start_angle)), 100 + (r * sin(start_angle)), \
				get_rgba(169, 169, 169, 255));
			r++;
		}
		start_angle += 0.01;
	}
}

void	mini_map(t_data *data)
{
	char	map_char;
	int		i;
	int		j;
	int		color;

	if (data->minimap.x_p >= 0 && data->minimap.y_p >= 0 && \
		data->minimap.x_p < data->map->map_width * MINI_TILE && \
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
				color = get_rgba(10, 10, 10, 100);
			protected_mppx(data->minimap.minimap_img, data->minimap.x, \
				data->minimap.y, color);
		}
	}
}

void	clear_minimap(mlx_image_t *img, int color)
{
	int	x;
	int	y;

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
