/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 04:24:03 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/31 04:24:51 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
