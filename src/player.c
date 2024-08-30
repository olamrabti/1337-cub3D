#include "../cub3d.h"

void ft_get_next_pos(t_data *data, int backward)
{
	double tmp_x;
	double tmp_y;
	double step;

	step = data->player.walk_direction * MOVE_SPEED;
	tmp_x = data->player.x + cos(data->player.rotation_angle) * step;
	tmp_y = data->player.y + sin(data->player.rotation_angle) * step;
	tmp_x += cos(data->player.rotation_angle + M_PI_2) * data->player.side_walk;
	tmp_y += sin(data->player.rotation_angle + M_PI_2) * data->player.side_walk;

	if (!is_wall(data, tmp_x - 3, tmp_y) && !is_wall(data, tmp_x + 3, tmp_y))
	{
		if (data->player.animation_area > 6 && !backward)
			data->player.x = tmp_x;
		else if (backward)
			data->player.x = tmp_x;
	}
	if (!is_wall(data, tmp_x, tmp_y - 3) && !is_wall(data, tmp_x, tmp_y + 3))
	{
		if (data->player.animation_area > 6 && !backward)
			data->player.y = tmp_y;
		else if (backward)
			data->player.y = tmp_y;
	}
}

void update_player(t_data *data, int backward)
{
	double factor;

	factor = 1000.0 / (1.0 + data->player.close_to_wall);
	factor = ((double)ROTATE / (factor));
	if (factor > (double)ROTATE)
		data->player.rotation_angle += data->player.turn_direction * factor;
	else
		data->player.rotation_angle += data->player.turn_direction * (double)ROT_FASTER;

	ft_get_next_pos(data, backward);
	clear_screen(data->img, get_rgba(0, 0, 0, 255));
	draw_map(data);
	cast_rays(data);

	// NOTE BONUS
	factor = floor(3 * (120.0 / (1.0 + data->player.animation_area)));
	if (data->player.animation_area > 50)
		ft_animation(data, 480, 820 + factor);
	else
		ft_animation(data, 480, 830 + factor * 3);
}

void ft_reset(t_data *data)
{
	data->player.walk_direction = 0;
	data->player.turn_direction = 0;
	data->player.side_walk = 0;
}

void key_event_handler(void *arg)
{
	t_data *data;
	int backward;

	data = arg;
	backward = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.turn_direction = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.turn_direction = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->player.walk_direction = -1;
		backward = 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->player.walk_direction = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->player.side_walk = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->player.side_walk = 1;
	if (data->player.walk_direction || data->player.turn_direction || data->player.side_walk)
		update_player(data, backward);
	ft_reset(data);
}
