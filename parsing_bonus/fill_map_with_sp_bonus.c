/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_with_sp_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:17:52 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/07 10:53:10 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_src/cub3d_bonus.h"

int	ft_fill_map_with_sp(t_map **map_st, t_addr **addr)
{
	char	**map;
	char	*new_line;
	int		i;
	int		len;

	i = 0;
	map = (*map_st)->map_tiles;
	while (i < (*map_st)->map_height)
	{
		len = ft_strlen(map[i]);
		if (len < (*map_st)->map_width)
		{
			new_line = (char *)safe_alloc(addr, \
				((*map_st)->map_width + 1), sizeof(char));
			if (!new_line)
				return (ERROR);
			ft_strlcpy(new_line, map[i], len + 1);
			ft_memset(new_line + len, ' ', (*map_st)->map_width - len);
			new_line[(*map_st)->map_width] = '\0';
			map[i] = new_line;
		}
		i++;
	}
	return (SUCCESS);
}
