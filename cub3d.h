#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
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

#endif