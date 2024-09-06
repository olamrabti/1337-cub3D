/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 05:12:50 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/06 10:45:03 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	draw_map(data);
	cast_rays(data);
	factor = floor(3 * (120.0 / (1.0 + data->player.animation_area)));
	if (data->player.animation_area > 50)
		ft_animation(data, 480, 820 + factor);
	else
		ft_animation(data, 480, 830 + factor * 3);
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
