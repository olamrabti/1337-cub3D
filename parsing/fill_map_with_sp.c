/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_with_sp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:17:52 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/12 12:06:38 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_fill_map_with_sp(t_data *data)
{
    int i;
    int map_width = data->map->map_width; // FIXME
    char **map = data->map->map_tiles;

    for (i = 0; i < data->map->map_height; i++)
    {
        int len = ft_strlen(map[i]);
        if (len < map_width)
        {
            char *new_line = (char *)ft_calloc_ac(&data->addr, (map_width + 1) , sizeof(char));
            if (!new_line)
                return ERROR;
            ft_strlcpy(new_line, map[i], len + 1);
            ft_memset(new_line + len, ' ', map_width - len);
            new_line[map_width] = '\0';
            // free(map[i]);
            map[i] = new_line;
        }
    }
    return SUCCESS;
}
