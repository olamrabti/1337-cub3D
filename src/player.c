#include "../cub3d.h"

 void draw_player(t_data data)
 {
	// printf ("player x : %d , player y : %d\n", player->x, player->x);
	draw_circle(data.img, data.player.y, data.player.x);
 }


// update player based on walk direction and turn direction
void update_player(t_data data)
{
    printf("%d\n", data.player.turn_direction);
    printf("%d\n", data.player.walk_direction);
}


// handle key event 
void key_event_handler(void *arg)
{
    t_data *data;

    data = arg;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->player.walk_direction = 1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.turn_direction = 1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->player.walk_direction = -1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.turn_direction = -1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->player.walk_direction = -1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->player.walk_direction = 1;
    else 
    {
		data->player.walk_direction = 0;
		data->player.turn_direction = 0;
    }
    if (data->player.walk_direction || data->player.turn_direction)
        update_player(*data);
}