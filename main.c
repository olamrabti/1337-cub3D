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

	while (i < 7)
	{
		j = 0;
		y = 0;
		while (map[i][j])
		{
			draw_rect(img,y, x, (int)map[i][j] - 48);
			j++;
			y += HEIGHT / 9;
		}
		i++;
		x += WIDTH / 9;
	}

 }


int	main(void)
{
	mlx_image_t	*img;
	mlx_t*    mlx;
	t_addr *addr;
	// t_player player;

	addr = NULL;

	char **map;

	map = parse_map(addr, "./maps/example.map");

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
	// ft_lstclear(&addr, free);
	return (EXIT_SUCCESS);
}