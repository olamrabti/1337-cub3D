/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_with_sp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:17:52 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/11 10:54:49 by olamrabt         ###   ########.fr       */
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
            char *new_line = (char *)malloc((map_width + 1) * sizeof(char));
            if (!new_line)
            {
                perror("Failed to allocate memory");
                return ERROR;
            }
            ft_strlcpy(new_line, map[i], len + 1);
            ft_memset(new_line + len, ' ', map_width - len);
            new_line[map_width] = '\0';
            free(map[i]);
            map[i] = new_line;
        }
    }
    return SUCCESS;
}
