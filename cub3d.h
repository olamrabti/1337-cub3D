#ifndef CUB3D_H
#define CUB3D_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

#include "MLX42/include/MLX42/MLX42.h"
#include "Libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <limits.h>

#define WIDTH 1080
#define HEIGHT 1080
#define TILE_SIZE 30
#define MINI_TILE 25

#define ERROR 1
#define SUCCESS 0

#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3

#define FOV_ANGL (M_PI / 3)
#define MOVE_SPEED 2.0

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
	int *f_rgb;
	int *c_rgb;
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
	double side_walk;
	double rotation_angle;
	double close_to_wall;
	double animation_area;
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
	double wall_height;
} t_ray;

typedef struct dda_step
{
	double d_x;
	double d_y;
	t_point next;
	t_point check_pt;
	double distance;
} t_dda;


typedef struct s_addr
{
	void				*address;
	struct s_addr		*nxt;
}	t_addr;

typedef struct s_minimap
{
	mlx_image_t *minimap_img;
	int x_p;
	int y_p;
	int x;
	int y;
	int color;
} t_minimap;

typedef struct s_data
{
	mlx_image_t	*img;
	mlx_texture_t **tx;
	mlx_t *mlx;
	t_addr *addr;
	t_player player;
	t_map *map;
	t_minimap minimap;
	double mouse_x;
	mlx_image_t		*frame;
	int frame_num;

}	t_data;

int		add_addr(t_addr **list, t_addr *new);
void	*safe_alloc(t_addr **addr, size_t count, size_t size); 
t_addr	*new_addr(char *value);
void	ft_addrclear(t_addr **lst, void (*del)(void *));

int get_rgba(int r, int g, int b, int a);
void protected_ppx(mlx_image_t *img, int x, int y, int color);
void clear_screen(mlx_image_t *img, int color);
void draw_map(t_data *data);

double normalize_angle(double angle);
int is_up(double angle);
int is_right(double angle);
double get_distance(t_data *data, double x, double y);
int is_wall(t_data *data, double x, double y);

void key_event_handler(void *arg);
void cast_rays(t_data *data);
int get_textures(t_data *data);
void render_tex_col(t_data *data, t_ray *ray, int x);
void update_player(t_data *data);


void    ft_error(int i);
char	*gc_itoa(int n, t_addr **addr);
char *get_next_line(int fd, t_data *data);
int ft_parsing(char *map_path, t_data *data);
int ft_strcmp(const char *s1, const char *s2);
int ft_parsing_map(char *map_path, t_data *data);
int ft_save_vars(char *map_path, t_data *data);
int ft_check_vars(t_data *data);
int ft_save_player_pos(t_data *data);
char *ft_bring_map(int fd, t_data *data);
char	**ft_split(char const *s, char c, t_data *data);
int ft_has_tabs(t_data *data);
int ft_split_map(t_data *data);
char	*gc_substr(char *s, unsigned int start, size_t len, t_addr **addr);
char	*gc_strdup(const char *s, t_addr **addr);
char	*gc_strjoin(char *s1, char *s2, t_addr **addr);
int ft_check_players(t_data *data);
int ft_fill_map_dimension(t_data *data);
int ft_double_check_vars(t_data *data);
int ft_fill_map_with_sp(t_data *data);
void ft_animation(t_data *data, int x, int y);
int ft_stores_f_c(t_data *data);
int ft_valide_wall_direction(char *line);
int ft_parse_map_path(char *map_path);
int ft_check_zero_surroundings(char **map, int i, int j);
int ft_valide_map(t_data *data);
int ft_read_map_lines(int fd, t_data *data, char **single_line_vars);
int ft_only_ones(char *str);
int ft_start_with_one(t_data *data);
int ft_parse_map_variables(char *map_path, t_data *data);


#endif