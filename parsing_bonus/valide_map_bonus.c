/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:25:51 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/07 10:54:01 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_src/cub3d_bonus.h"

int	ft_fill_map_dimension_suite(t_map **map, int max_width, int i)
{
	if (i == 0)
		return (ERROR);
	(*map)->map_width = max_width;
	(*map)->map_height = i;
	if (i > max_width)
		(*map)->tile_size = WIDTH / i;
	else
		(*map)->tile_size = HEIGHT / max_width;
	if ((*map)->tile_size > TILE_SIZE)
		(*map)->tile_size = TILE_SIZE * 0.3;
	return (SUCCESS);
}

int	ft_fill_map_dimension(t_map **map_st)
{
	char	**map;
	int		i;
	int		max_width;
	int		line_length;

	if (!map_st || !(*map_st))
		return (ERROR);
	map = (*map_st)->map_tiles;
	max_width = 0;
	i = 0;
	while (map[i])
	{
		line_length = ft_strlen(map[i]);
		if (line_length > max_width)
			max_width = line_length;
		i++;
	}
	if (ft_fill_map_dimension_suite(map_st, max_width, i) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ft_only_ones(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	ft_start_with_one(t_map **map_st)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = (*map_st)->map_tiles;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
