/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 04:27:33 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/05 10:35:49 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	protected_ppx(mlx_image_t *img, int x, int y, int color)
{
	if (x <= WIDTH && x >= 0 && y >= 0 && y <= HEIGHT)
		mlx_put_pixel(img, x, y, color);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}


int is_wall_p(t_data *data, double p_x, double p_y)
{
	int radius;
	double x;
	double y;

	radius = 4;
	x = p_x - radius;
	while (x <= p_x + radius)
	{
		y = p_y - radius;
		while (y <= p_y + radius)
		{
			if (pow(x - p_x, 2) + pow(y - p_y, 2) <= pow(radius, 2))
				if (is_wall(data, x, y))
					return 1;
			y++;
		}
		x++;
	}
	return (0);
}

void	clear_screen(mlx_image_t *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			protected_ppx(img, x, y, color);
			x++;
		}
		y++;
	}
}