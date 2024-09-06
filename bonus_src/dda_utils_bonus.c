/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 04:57:33 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/06 10:47:28 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	normalize_angle(double angle)
{
	double	normalized;

	normalized = fmod(angle, 2 * M_PI);
	if (normalized < 0.0)
		normalized += 2 * M_PI;
	return (normalized);
}

double	get_distance(t_data *data, double x, double y)
{
	double	delta_x;
	double	delta_y;

	delta_x = x - data->player.x;
	delta_y = y - data->player.y;
	return (sqrt((delta_x * delta_x) + (delta_y * delta_y)));
}

int	is_up(double angle)
{
	return (angle > M_PI);
}

int	is_right(double angle)
{
	return (angle >= (3 * M_PI / 2) || angle < M_PI / 2);
}

int	is_wall(t_data *data, double x, double y)
{
	double	map_x;
	double	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (map_x > 0 && map_x < data->map->map_width && \
	map_y > 0 && map_y < (data->map->map_height))
	{
		if (data->map->map_tiles[(int)map_y][(int)map_x] != '0')
			return (1);
		return (0);
	}
	return (1);
}
