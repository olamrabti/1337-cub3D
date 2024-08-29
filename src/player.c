#include "../cub3d.h"


void update_player(t_data *data, int backward)
{
	double tmp_x;
	double tmp_y;
	double step;
	double factor;

	factor = 1000.0 / (1.0 + data->player.close_to_wall);

	factor = ((double)ROTATE / (factor));
	if (factor > (double)ROTATE)
		data->player.rotation_angle += data->player.turn_direction * factor;
	else
		data->player.rotation_angle += data->player.turn_direction * (double)ROT_FASTER;
	step = data->player.walk_direction * MOVE_SPEED;
	tmp_x = data->player.x + cos(data->player.rotation_angle) * step;
	tmp_y = data->player.y + sin(data->player.rotation_angle) * step;

	tmp_x += cos(data->player.rotation_angle + M_PI_2) * data->player.side_walk;
	tmp_y += sin(data->player.rotation_angle + M_PI_2) * data->player.side_walk ;

	if (!is_wall(data, tmp_x - 3, tmp_y) && !is_wall(data, tmp_x + 3, tmp_y))
	{
		if (data->player.animation_area > 6 && !backward)
			data->player.x = tmp_x;
		else if (backward)
			data->player.x = tmp_x;
	}

	if (!is_wall(data, tmp_x, tmp_y - 3) && !is_wall(data, tmp_x, tmp_y + 3) )
	{
		if (data->player.animation_area > 6 && !backward)
			data->player.y = tmp_y;
		else if (backward)
			data->player.y = tmp_y;
	}
	clear_screen(data->img, get_rgba(0, 0, 0, 255));
	draw_map(data);
	cast_rays(data);
	factor = floor(3 * (120.0 / (1.0 + data->player.animation_area)));
	if (data->player.animation_area > 50)
		ft_animation(data, 480, 820 + factor);
	else
		ft_animation(data, 480, 830 + factor * 3);
}


mlx_image_t	*ft_get_frame(t_data *data)
{
	char *path;
	mlx_texture_t *texture;
	mlx_image_t *frame;

	if (data->frame)
		mlx_delete_image(data->mlx, data->frame);
	path = ft_strjoin("./animation/", ft_itoa(data->frame_num));
	path = ft_strjoin(path, ".png");

	texture = mlx_load_png(path);
	if (!texture)
		exit(EXIT_FAILURE);
	frame = mlx_texture_to_image(data->mlx, texture);
	mlx_delete_texture(texture);
	if (!frame)
		exit(EXIT_FAILURE);
	return (frame);
}


void ft_animation(t_data *data , int x , int y)
{
	static	int i = 1;
	
	if (i == 24)
		i = 1;
	data->frame_num = i;
	data->frame = ft_get_frame(data);
	mlx_image_to_window(data->mlx, data->frame, x, y);
	i++;
}

// handle key event
void key_event_handler(void *arg)
{
	t_data *data;
	int backward;

	data = arg;
	backward = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	// if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	// 	ft_animation(data);
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
	data->player.walk_direction = 0;
	data->player.turn_direction = 0;
	data->player.side_walk = 0;
}
