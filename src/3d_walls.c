/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_walls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 04:18:52 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/06 10:28:43 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_textures(t_data *data)
{
	data->tx = safe_alloc(&data->addr, 4, sizeof(mlx_texture_t));
	if (!data->tx)
		return (0);
	data->tx[0] = mlx_load_png(data->map->no_texture_path);
	data->tx[1] = mlx_load_png(data->map->so_texture_path);
	data->tx[2] = mlx_load_png(data->map->we_texture_path);
	data->tx[3] = mlx_load_png(data->map->ea_texture_path);
	if (!data->tx[0] || !data->tx[1] || !data->tx[2] || !data->tx[3])
		return (ft_putstr_fd("Error\nTexture Loading Error\n", 2), 0);
	return (1);
}

void	delete_textures(t_data *data)
{
	if (!data->tx)
		return ;
	if (data->tx[0])
		mlx_delete_texture(data->tx[0]);
	if (data->tx[1])
		mlx_delete_texture(data->tx[1]);
	if (data->tx[2])
		mlx_delete_texture(data->tx[2]);
	if (data->tx[3])
		mlx_delete_texture(data->tx[3]);
}

void	texture_ppx(t_data *data, double x, double y, t_ray *ray)
{
	unsigned int	rel_x;
	unsigned int	rel_y;
	int				color;
	int				idx;

	rel_x = (fmod(ray->end_y, TILE_SIZE) / TILE_SIZE) * \
			data->tx[ray->direction]->width;
	if (ray->direction == NORTH || ray->direction == SOUTH)
		rel_x = (fmod(ray->end_x, TILE_SIZE) / TILE_SIZE) * \
				data->tx[ray->direction]->width;
	if (rel_x < 0 || rel_x >= data->tx[ray->direction]->width)
		return ;
	rel_y = ((y - (HEIGHT / 2) + (ray->wall_height / 2)) / ray->wall_height) * \
			data->tx[ray->direction]->height;
	if (rel_x < 0 || rel_x >= data->tx[ray->direction]->width)
		return ;
	idx = (rel_y * data->tx[ray->direction]->width + rel_x) * \
		data->tx[ray->direction]->bytes_per_pixel;
	color = get_rgba(data->tx[ray->direction]->pixels[idx], \
			data->tx[ray->direction]->pixels[idx + 1], \
			data->tx[ray->direction]->pixels[idx + 2], \
			data->tx[ray->direction]->pixels[idx + 3]);
	if (x < WIDTH && x >= 0 && y >= 0 && y < HEIGHT)
		protected_ppx(data->img, x, y, color);
}

void	render_r_and_c(t_data *data, double wall_top, double wall_bottom, int x)
{
	int	i;
	int	color;

	i = 0;
	color = get_rgba(data->map->c_rgb[0], data->map->c_rgb[1], \
	data->map->c_rgb[2], 200);
	while (i < wall_top)
	{
		protected_ppx(data->img, x, i, color);
		i++;
	}
	i = wall_bottom;
	color = get_rgba(data->map->f_rgb[0], data->map->f_rgb[1], \
	data->map->f_rgb[2], 200);
	while (i < HEIGHT)
	{
		protected_ppx(data->img, x, i, color);
		i++;
	}
}

void	render_tex_col(t_data *data, t_ray *ray, int x)
{
	double	wall_height;
	double	wall_top;
	double	wall_bottom;
	double	scale;

	scale = 12.0;
	wall_height = ((HEIGHT / ray->distance) * scale);
	ray->wall_height = wall_height;
	wall_top = (HEIGHT / 2) - (wall_height / 2);
	wall_bottom = wall_top + wall_height;
	render_r_and_c(data, wall_top, wall_bottom, x);
	while (wall_top < wall_bottom)
	{
		texture_ppx(data, x, wall_top, ray);
		wall_top++;
	}
}
