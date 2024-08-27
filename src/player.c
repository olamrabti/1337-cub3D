#include "../cub3d.h"


int is_near_wall(t_data *data)
{
	double tmp_x;
	double tmp_y;
	double fov_angles[3];
	int i;
	int j;

	fov_angles[0] = data->player.rotation_angle - (FOV_ANGL / 4);
	fov_angles[1] = data->player.rotation_angle;
	fov_angles[2] = data->player.rotation_angle + (FOV_ANGL / 4);

	i = 0;
	j = 0;
	while (i < 3)
	{
		tmp_x = data->player.x + cos(fov_angles[i]) * (TILE_SIZE);
		tmp_y = data->player.y + sin(fov_angles[i]) * (TILE_SIZE);

		if (is_wall(data, tmp_x, tmp_y))
			j++;
		i++;
	}
	if (j < 2)
		return 0;
	return 1;
}

void update_player(t_data *data)
{
	double tmp_x;
	double tmp_y;
	double step;
	double factor;



	factor = 1.0 / (1.0 + data->player.close_to_wall);
	// if (is_near_wall(data) && factor < 0.0005)
	// {
		// printf("ROT :%.4f\n", (double)ROTATE);
		// printf("ROT_FASTER :%.4f\n", (double)ROT_FASTER);
		// printf("fmod :%.4f\n", ((double)ROTATE / (factor * 1000)));
		// printf("%.4f\n", factor);
		factor = ((double)ROTATE / (factor * 1000));
		if (factor > (double)ROTATE)
			data->player.rotation_angle += data->player.turn_direction * factor;
		else
			data->player.rotation_angle += data->player.turn_direction * (double)ROT_FASTER;
	// }
	// else
	// 	data->player.rotation_angle += data->player.turn_direction * ((double)ROT_FASTER);
	step = data->player.walk_direction * MOVE_SPEED;

	tmp_x = data->player.x + cos(data->player.rotation_angle) * step;
	tmp_y = data->player.y + sin(data->player.rotation_angle) * step;

	tmp_x += cos(data->player.rotation_angle + M_PI_2) * data->player.side_walk * MOVE_SPEED;
	tmp_y += sin(data->player.rotation_angle + M_PI_2) * data->player.side_walk * MOVE_SPEED;

	if (!is_wall(data, tmp_x - 3, tmp_y) && !is_wall(data, tmp_x + 3, tmp_y) &&
		!is_wall(data, tmp_x, tmp_y - 3) && !is_wall(data, tmp_x, tmp_y + 3))
	{
		data->player.x = tmp_x;
		data->player.y = tmp_y;
	}


	clear_screen(data->img, get_rgba(0, 0, 0, 255));
	draw_map(data);
	cast_rays(data);
}

// void update_player(t_data *data)
// {
// 	int step;
// 	double tmp_x;
// 	double tmp_y;

// 	tmp_x = data->player.x + cos(data->player.rotation_angle - (FOV_ANGL / 2)) * (TILE_SIZE);
// 	tmp_y = data->player.y + sin(data->player.rotation_angle - (FOV_ANGL / 2)) * (TILE_SIZE);

// 	if (is_wall(data, tmp_x, tmp_y) || is_wall(data, data->player.x + cos(data->player.rotation_angle + (FOV_ANGL / 2)) *\
// 	 (TILE_SIZE), data->player.y + sin(data->player.rotation_angle + (FOV_ANGL / 2)) * (TILE_SIZE)))
// 		data->player.rotation_angle += data->player.turn_direction * ROT_FASTER;

// 	tmp_x = data->player.x + cos(data->player.rotation_angle) * (TILE_SIZE);
// 	tmp_y = data->player.y + sin(data->player.rotation_angle) * (TILE_SIZE);

// 	if (is_wall(data, tmp_x, tmp_y))
// 		data->player.rotation_angle += data->player.turn_direction * ROT_FASTER;
// 	else
// 		data->player.rotation_angle += data->player.turn_direction * ROTATE;

// 	step = data->player.walk_direction * MOVE_SPEED;
// 	tmp_x = data->player.x + cos(data->player.rotation_angle) * step;
// 	tmp_y = data->player.y + sin(data->player.rotation_angle) * step;
// 	if (!is_wall(data, tmp_x - 3, tmp_y) && !is_wall(data, tmp_x + 3, tmp_y) \
// 	&& !is_wall(data, tmp_x, tmp_y - 3) && !is_wall(data, tmp_x, tmp_y + 3))
// 	{
// 		data->player.x += cos(data->player.rotation_angle) * step;
// 		data->player.y += sin(data->player.rotation_angle) * step;
// 	}

// 	clear_screen(data->img, get_rgba(0, 0, 0, 255));
// 	draw_map(data);
// 	cast_rays(data);
// }

// handle key event
void key_event_handler(void *arg)
{
	t_data *data;

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
	if (data->player.walk_direction || data->player.turn_direction || data->player.side_walk)
		update_player(data);
	data->player.walk_direction = 0;
	data->player.turn_direction = 0;
	data->player.side_walk = 0;
}