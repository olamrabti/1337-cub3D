/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_player_pos_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:27:09 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/01 23:38:31 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_src/cub3d_bonus.h"

int	ft_is_player_direction(char c)
{
	if (c == 'N')
		return (1);
	if (c == 'S')
		return (1);
	if (c == 'E')
		return (1);
	if (c == 'W')
		return (1);
	return (0);
}

int	ft_check_players(t_map **map)
{
	char	**temp;
	int		i;
	int		j;
	int		count;

	count = 0;
	temp = (*map)->map_tiles;
	i = 0;
	j = 0;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (ft_is_player_direction(temp[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return (ERROR);
	return (SUCCESS);
}

int	ft_save_player_pos(t_map **map)
{
	char	**temp;
	int		i;
	int		j;

	temp = (*map)->map_tiles;
	i = 0;
	j = 0;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (ft_is_player_direction(temp[i][j]))
			{
				(*map)->player_direction = temp[i][j];
				(*map)->player_x = j;
				(*map)->player_y = i;
				temp[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
