#include "cub3d.h"

void	hook(void* arg)
{
	if (mlx_is_key_down((mlx_t*)arg, MLX_KEY_ESCAPE))
		mlx_close_window((mlx_t*)arg);
}

 void draw_map (char **map, mlx_image_t *img)
 {
	int i;
	int j;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;

	while (x <= WIDTH / SIZE)
	{
		j = 0;
		y = 0;
		// draw line of rects
		while (y <= HEIGHT / SIZE )
		{
			draw_rect(img,x, y, (int)map[i][j] - 48);
			j++;
			y += SIZE ;
		}
		i++;
		x += SIZE;
		// then move to the other colomn of rects
	}

 }
// update player position

int	main(void)
{
	mlx_image_t	*img;
	mlx_t*    mlx;
	// t_player player;

	char* map[12] = {
		"111111111111",
		"100000000001",
		"100000000001",
		"100000000001",
		"100000000001",
		"100000000001",
		"100000000001",
		"100000000001",
		"100000000001",
		"100000000001",
		"100000000001",
		"111111111111"
	};
	
	// player.x = WIDTH/2;
	// player.y = HEIGHT/2;
	// player.turn_direction = 0;
	// player.walk_direction = 0;
	// player.rotation_angle = M_PI / 2;
	// player.move_speed = 3.0;
	// player.rot_speed = 2 * M_PI / 180;

	// TODO protect MLX utils if each one fails
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, img, 0, 0);
	draw_map(map, img);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}