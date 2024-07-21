#ifndef CUB3D_H
#define CUB3D_H

#include "./MLX42/include/MLX42/MLX42.h"
#include "./Libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>


#define WIDTH 600
#define HEIGHT 600
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

typedef struct s_addr
{
	void				*address;
	struct s_addr		*nxt;
}	t_addr;


int		add_addr(t_addr **list, t_addr *new);
// void	ft_lstclear(t_addr **lst, void (*del)(void *));
void	*ft_calloc_ac(t_addr **addr, size_t count, size_t size);
t_addr	*new_addr(char *value);
char **parse_map(t_addr *addr, char *filename);
void draw_rect(mlx_image_t *img, int x , int y, int color);

#endif