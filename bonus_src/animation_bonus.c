/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 04:53:40 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/06 10:43:10 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

mlx_image_t	*ft_get_frame(t_data *data)
{
	mlx_texture_t	*texture;
	mlx_image_t		*frame;
	char			*path;
	static int		direction;

	if (data->frame)
		mlx_delete_image(data->mlx, data->frame);
	if (data->player.turn_direction)
		direction = data->player.turn_direction;
	if (data->player.side_walk)
		direction = data->player.side_walk;
	if (direction <= 0)
		path = gc_strjoin("./animation/l", \
		gc_itoa(data->frame_num, &data->addr), &data->addr);
	else
		path = gc_strjoin("./animation/r", \
		gc_itoa(data->frame_num, &data->addr), &data->addr);
	path = gc_strjoin(path, ".png", &data->addr);
	texture = mlx_load_png(path);
	if (!texture)
		exit(EXIT_FAILURE);
	frame = mlx_texture_to_image(data->mlx, texture);
	if (!frame)
		exit(EXIT_FAILURE);
	return (mlx_delete_texture(texture), frame);
}

void	ft_animation(t_data *data, int x, int y)
{
	static int	i;

	if (i == 24 || i == 0)
		i = 1;
	data->frame_num = i;
	i++;
	data->frame = ft_get_frame(data);
	mlx_image_to_window(data->mlx, data->frame, x, y);
}
