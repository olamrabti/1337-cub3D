#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include </home/oussama/Desktop/1337-cub3D/MLX42/include/MLX42/MLX42.h>
#include <math.h>

#define WIDTH 576
#define HEIGHT 576

typedef struct player
{
	int x;
	int y;
	int turn_direction;
	int walk_direction;
	double rotation_angle;
	double move_speed;
	double rot_speed;
} t_player;

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <time.h>

static mlx_image_t	*g_img;
double raduis = 1;

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
void map(double *x_r, double *y_r, int x, int y)
{
	*x_r = (double)x /(WIDTH/4) - 2.0;
	*y_r = (double)y /(HEIGHT/4) - 2.0; 
}

int circel(double x_r, double y_r, double raduis)
{
	if (  x_r *x_r + y_r * y_r  < (raduis * raduis))
		return (1);
	return (0);
}

void put_player(t_player *player)
{
	double x_r , y_r;
	int x = 0 ;
	int y ; 

	while (x < WIDTH)
	{
		y = 0;
		while ( y < HEIGHT  )
		{
			map(&x_r, &y_r, x, y);
			if (circel(x_r, y_r, 0.05))
				mlx_put_pixel(g_img, x, y, get_rgba(255,0,0,255));
			y++;
		}
		x++;
	}
}
void put_rect(int size, int x,int y, int color)
{
	int col = x + size;
	int line = y + size;
	int tmp= y;
	while (x < col )
	{
		y = tmp;
		while (y < line)
		{
			if (color == 1)
				mlx_put_pixel(g_img, x, y, get_rgba(0, 0, 0,255));
			else
				mlx_put_pixel(g_img, x, y, get_rgba(155, 155, 255, 255));
			y++;
		}
		x++;
	}
}
void	draw_map(char **map, int size, int x, int y)
{
	int i=0;
	int j=0;
	while (i < WIDTH/size)
	{
		y = 0;
		j = 0;
		while (j < HEIGHT/size)
		{
			if (map[i][j] == '1')
				put_rect(size, x, y, 1);
			j++;
			y +=size;
		}
		x +=size;
		i++;
	}
}

void	hook(void* param)
{
	mlx_t* mlx;
	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, g_img);
	if (mlx_is_key_down(mlx, MLX_KEY_R))
	{
		raduis =0;
	}

}

int32_t	main(void)
{
	mlx_t*    mlx;
	t_player player;

	player.x = WIDTH/2;
	player.y = HEIGHT/2;
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.rotation_angle = M_PI / 2;
	player.move_speed = 3.0;
	player.rot_speed = 2 * M_PI / 180;

	int x=0, y = 0;
		char *map[18] = {
		"111111111111111111",
		"100000000000000001",
		"101100010110111101",
		"101000101010010011",
		"110110110101011011",
		"101000101010010011",
		"110110110111011011",
		"101000101010010011",
		"110101010110110101",
		"101000101010010011",
		"101011011011011011",
		"101000101010010011",
		"110101010101010101",
		"101000101010010011",
		"101101110111010111",
		"101000101010010011",
		"101000101010010011",
		"111111111111111111"
		};

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, g_img, 0, 0);
	double x_r = 0, y_r=0;
	draw_map(map, 32, x, y);
	put_player(&player);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}