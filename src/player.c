/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 04:29:01 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/06 10:33:55 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	ft_get_next_pos(t_data *data)
{
	double	tmp_x;
	double	tmp_y;
	double	step;

	step = data->player.walk_direction * MOVE_SPEED;
	tmp_x = data->player.x + cos(data->player.rotation_angle) * step;
	tmp_y = data->player.y + sin(data->player.rotation_angle) * step;
	tmp_x += cos(data->player.rotation_angle + M_PI_2) * data->player.side_walk;
	tmp_y += sin(data->player.rotation_angle + M_PI_2) * data->player.side_walk;
	if (!is_wall_p(data, tmp_x, data->player.y))
		data->player.x = tmp_x;
	if (!is_wall_p(data, data->player.x, tmp_y))
		data->player.y = tmp_y;
}

void	update_player(t_data *data)
{
	double	factor;
	double	rot_speed;

	factor = 1000.0 / (1.0 + data->player.close_to_wall);
	rot_speed = (((2 * M_PI) / 160) / (factor));
	if (rot_speed > ((2 * M_PI) / 160))
		data->player.rotation_angle += data->player.turn_direction * rot_speed;
	else
	{
		rot_speed = ((2 * M_PI) / 100);
		data->player.rotation_angle += data->player.turn_direction * rot_speed;
	}
	ft_get_next_pos(data);
	clear_screen(data->img, get_rgba(0, 0, 0, 255));
	cast_rays(data);
}

void	ft_reset(t_data *data)
{
	data->player.walk_direction = 0;
	data->player.turn_direction = 0;
	data->player.side_walk = 0;
}

void	key_event_handler(void *arg)
{
	t_data	*data;

	data = arg;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.turn_direction = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.turn_direction = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->player.walk_direction = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->player.walk_direction = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->player.side_walk = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->player.side_walk = 1;
	if (data->player.walk_direction || data->player.turn_direction \
		|| data->player.side_walk)
		update_player(data);
	ft_reset(data);
}
