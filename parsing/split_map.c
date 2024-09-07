/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:23:46 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/07 10:42:58 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	ft_split_map(t_map **map, t_addr **addr)
{
	int		i;
	char	**temp;

	(*map)->map_tiles = ft_split((*map)->single_line_map, '\n', addr);
	if (!(*map)->map_tiles)
		return (ft_error(7), (ERROR));
	i = 0;
	temp = (*map)->map_tiles;
	while (temp[i])
	{
		if (ft_all_spaces(temp[i]))
			temp[i] = NULL;
		i++;
	}
	return (SUCCESS);
}

int	ft_has_tabs(t_map **map)
{
	char	**temp;
	int		i;
	int		j;

	temp = (*map)->map_tiles;
	i = 0;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (temp[i][j] == '\t')
				return (ft_error(8), (ERROR));
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
