#include "../cub3d.h"

 void draw_player(t_data *data)
 {
	// printf ("player x : %d , player y : %d\n", player.x, player.x);
	draw_circle(data->img, data->player.x, data->player.y);
	// draw_rays(data);
 }


// update player based on walk direction and turn direction
void update_player(t_data *data)
{
	int step;
	int projected_x;
	int projected_y;

	data->player.rotation_angle += data->player.turn_direction * ROT_SPEED;
	step = data->player.walk_direction * MOVE_SPEED;
	projected_x = (int)data->player.x + cos(data->player.rotation_angle) * step;
	projected_y = (int)data->player.y + sin(data->player.rotation_angle) * step;
    // printf("%d\n", data->player.turn_direction);
    // printf("%d\n", data->player.walk_direction);
    // printf("rot : %d\n", data->player.rotation_angle);
    // printf("step : %d\n", step);

    // printf("x : %d , y : ", data->player.x);
    // printf("%d\n", data->player.y);

	// if (projected_x < SIZE * 8 && projected_x > SIZE && projected_y < SIZE * 6 && projected_y > SIZE)
	if (is_wall(data, projected_x, projected_y) == 0)
	{
		// printf("is wall : %d\n", is_wall(*data, data->player.x, data->player.y));

		data->player.x += cos(data->player.rotation_angle) * step;
		data->player.y += sin(data->player.rotation_angle) * step;
   		clear_screen(data->img, get_rgba(0, 0, 0, 255));
		draw_map(data);
		draw_player(data);
	}
}


// handle key event 
void key_event_handler(void *arg)
{
    t_data *data;

    data = arg;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.turn_direction = 1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.turn_direction = -1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->player.walk_direction = -1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->player.walk_direction = 1;
    // else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		// data->player.walk_direction = 1;
	// else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		// data->player.walk_direction = -1;
    else 
    {
		data->player.walk_direction = 0;
		data->player.turn_direction = 0;
    }
    if (data->player.walk_direction || data->player.turn_direction)
        update_player(data);
}