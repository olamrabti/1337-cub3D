#include "../cub3d.h"

 void draw_player(t_data *data)
 {
	// draw_view(data);
	cast_rays(data);
 }

void update_player(t_data *data)
{
	int step;
	double projected_x;
	double projected_y;

	projected_x = data->player.x + cos(data->player.rotation_angle) * (TILE_SIZE / 2);
	projected_y = data->player.y + sin(data->player.rotation_angle) * (TILE_SIZE / 2);
	if (!is_wall(data, projected_x , projected_y))
		data->player.rotation_angle += data->player.turn_direction * ROT_SPEED;
	else
	{
		data->player.rotation_angle += data->player.turn_direction * ROT_FASTER;
		printf(" %.f ,,", data->player.rotation_angle);
	}

	step = data->player.walk_direction * MOVE_SPEED;
	projected_x = data->player.x + cos(data->player.rotation_angle) * (step);
	projected_y = data->player.y + sin(data->player.rotation_angle) * (step);
	if (!is_wall(data, projected_x - 5, projected_y) && !is_wall(data, projected_x + 5, projected_y) \
	&& !is_wall(data, projected_x, projected_y - 5) && !is_wall(data, projected_x, projected_y + 5))
	{
		data->player.x += cos(data->player.rotation_angle) * step;
		data->player.y += sin(data->player.rotation_angle) * step;
	} 
	
	clear_screen(data->img, get_rgba(0, 0, 0, 255));
	draw_map(data);
	draw_player(data);
}

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
    // else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		// data->player.walk_direction = 1;
	// else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		// data->player.walk_direction = -1;
    if (data->player.walk_direction || data->player.turn_direction)
        update_player(data);
	data->player.walk_direction = 0;
	data->player.turn_direction = 0;
}