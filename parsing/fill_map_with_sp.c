/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_with_sp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:17:52 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/30 16:00:39 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_fill_map_with_sp(t_data *data)
{
	char	**map;
	char	*new_line;
	int		i;
	int		len;

	i = 0;
	map = data->map->map_tiles;
	while (i < data->map->map_height)
	{
		len = ft_strlen(map[i]);
		if (len < data->map->map_width)
		{
			new_line = (char *)safe_alloc(&data->addr, \
				(data->map->map_width + 1), sizeof(char));
			if (!new_line)
				return (ERROR);
			ft_strlcpy(new_line, map[i], len + 1);
			ft_memset(new_line + len, ' ', data->map->map_width - len);
			new_line[data->map->map_width] = '\0';
			map[i] = new_line;
		}
		i++;
	}
	return (SUCCESS);
}
