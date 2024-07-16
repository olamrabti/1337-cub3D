#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include </home/oussama/Desktop/1337-cub3D/MLX42/include/MLX42/MLX42.h>
#include <math.h>

#define WIDTH 500
#define HEIGHT 500
#define SIZE 20

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00

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


void draw_rect(mlx_image_t *img, int x , int y, int color);

#endif