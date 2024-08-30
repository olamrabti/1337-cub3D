/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:25:51 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/30 03:49:50 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int ft_fill_map_dimension_suite(t_data *data, int max_width, int i)
{
    if (i == 0)
        return (ERROR);
    data->map->map_width = max_width;
    data->map->map_height = i;
     if (i > max_width)
        data->map->tile_size = WIDTH / i;
    else
        data->map->tile_size = HEIGHT / max_width;
    if (data->map->tile_size > TILE_SIZE)
        data->map->tile_size = TILE_SIZE * 0.3;
    return (SUCCESS);
}

int ft_fill_map_dimension(t_data *data)
{
    int i;
    int max_width;
    char **map;
    int line_length;

    if (!data)
        return (ERROR);
    map = data->map->map_tiles;
    max_width = 0;
    i = 0;
    while (map[i])
    {
        line_length = ft_strlen(map[i]);
        if (line_length > max_width)
            max_width = line_length;
        i++;
    }
    if (ft_fill_map_dimension_suite(data, max_width, i) == ERROR)
        return ERROR;
    return (SUCCESS);
}

int ft_only_ones(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '1')
            return ERROR;
        i++;
    }
    return SUCCESS;
}

int ft_start_with_one(t_data *data)
{
    char **map;
    int i;
    int j;

    i = 0;
    map = data->map->map_tiles;
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


