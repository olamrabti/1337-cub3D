#include "cub3d.h"


void	hook(void* arg)
{
	if (mlx_is_key_down((mlx_t*)arg, MLX_KEY_ESCAPE))
		mlx_close_window((mlx_t*)arg);
}

int	main(void)
{
	mlx_image_t	*g_img;
	mlx_t*    mlx;
	t_player player;

	player.x = WIDTH/2;
	player.y = HEIGHT/2;
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.rotation_angle = M_PI / 2;
	player.move_speed = 3.0;
	player.rot_speed = 2 * M_PI / 180;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}