#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42/include/MLX42/MLX42.h"
#include "Libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>


#define WIDTH 600
#define HEIGHT 600
#define SIZE 20


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

typedef struct s_addr
{
	void				*address;
	struct s_addr		*nxt;
}	t_addr;

typedef struct s_data
{
	mlx_image_t	*img;
	mlx_t	*mlx;
	t_addr *addr;
	t_player player;
	char **map;
	int lines;
	// int tile_size;

}	t_data;

int		add_addr(t_addr **list, t_addr *new);
void	*ft_calloc_ac(t_addr **addr, size_t count, size_t size);
t_addr	*new_addr(char *value);
void	ft_addrclear(t_addr **lst, void (*del)(void *));
// char **parse_map(t_addr *addr, char *filename);
void parse_map(t_data *data, char *filename);
void draw_rect(mlx_image_t *img, int x , int y, int color);
void draw_player(t_data data);
int get_rgba(int r, int g, int b, int a);
void draw_circle(mlx_image_t *img, int x0, int y0);
void key_event_handler(void *arg);
void draw_map (t_data *data);
double draw_line(t_data data, int x1, int y1, int x2, int y2);
void draw_rays(t_data data);
int is_wall(t_data data, int x, int y);
void clear_screen(mlx_image_t *img, int color);
#endif