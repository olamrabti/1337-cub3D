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

#define WIDTH 1080
#define HEIGHT 1080
#define TILE_SIZE 30
#define CENTER_X (WIDTH / 2)
#define CENTER_Y (HEIGHT / 2)

#define ERROR 1
#define SUCCESS 0

#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3

#define FOV_ANGL (M_PI / 3)
#define MOVE_SPEED 2.5
#define ROT_SPEED (2 * M_PI / 160)
#define ROT_FASTER (2 * M_PI / 100)

typedef struct s_map
{
	int map_width;
	int map_height;
	double player_x;
	double player_y;
	int tile_size;
	char **map_tiles;
	char *no_texture_path;
	char *so_texture_path;
	char *we_texture_path;
	char *ea_texture_path;
	char *f_color;
	char *c_color;
	char player_direction;
	char *single_line_map;
	char *single_line_vars;

} t_map;

typedef struct player
{
	double x;
	double y;
	double turn_direction;
	double walk_direction;
	double rotation_angle;
} t_player;

typedef struct point
{
	double x;
	double y;
} t_point;

typedef struct ray
{
	double end_x;
	double end_y;
	double angle;
	double distance;
	int direction;
} t_ray;

typedef struct dda_step
{
	double d_x;
	double d_y;
	t_point first;
	t_point check_pt;
	double distance;
} t_dda;


typedef struct s_addr
{
	void				*address;
	struct s_addr		*nxt;
}	t_addr;

typedef struct s_data
{
	mlx_image_t	*img;
	mlx_texture_t **tx;
	mlx_t *mlx;
	t_addr *addr;
	t_player player;
	t_map *map;
}	t_data;

int		add_addr(t_addr **list, t_addr *new);
void	*ft_calloc_ac(t_addr **addr, size_t count, size_t size);
t_addr	*new_addr(char *value);
void	ft_addrclear(t_addr **lst, void (*del)(void *));


void key_event_handler(void *arg);
int get_rgba(int r, int g, int b, int a);
void protected_ppx(mlx_image_t *img, int x, int y, int color);
void clear_screen(mlx_image_t *img, int color);
void draw_rect(t_data *data, int x, int y, int color);
void draw_player(t_data *data);
void draw_circle(mlx_image_t *img, int x0, int y0);
void draw_view(t_data *data, double scale);
void draw_map(t_data *data);
double draw_line(t_data *data, double x1, double y1, double x2, double y2, int color);
double normalize_angle(double angle);
// dda
int is_wall(t_data *data, double x, double y) ;
double get_distance(t_data *data, double x, double y);
void cast_rays(t_data *data); // change name later
void render_wall(t_data *data, double distance, int ray_index, int direction);
int get_textures(t_data *data);
void render_tex_col(t_data *data, t_ray *ray, int x);

//=======================================================================
//                             parsing                                 //
//=======================================================================

int ft_parsing(char *map_path, t_data *data);
// int ft_strcmp(const char *s1, const char *s2);
int ft_parsing_map(char *map_path, t_data *data);
int ft_save_vars(char *map_path, t_data *data);
int ft_valide_wall_direction(char *line);
int ft_check_vars(t_data *data);
int ft_save_player_pos(t_data *data);
char *ft_bring_map(int fd);

int ft_has_tabs(t_data *data);
int ft_split_map(t_data *data);

int ft_check_players(t_data *data);
int ft_fill_map_dimension(t_data *data);

int ft_valide_map(t_data *data);

int ft_double_check_vars(t_data *data);
int ft_fill_map_with_sp(t_data *data);

#endif