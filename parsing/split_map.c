/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:23:46 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/30 03:56:38 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int  ft_all_spaces(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t')
            return 0;
        i++;
    }
    return 1;
}

int ft_split_map(t_data *data)
{
    int i;
    char **temp;

    data->map->map_tiles = ft_split(data->map->single_line_map, '\n', data);
    if (!data->map->map_tiles)
        return (ERROR);
    i = 0;
    temp = data->map->map_tiles;
    while (temp[i])
    {
        if (ft_all_spaces(temp[i]))
            temp[i] = NULL;
        i++;
    }
    return (SUCCESS);
}

int ft_has_tabs(t_data *data)
{
    char **temp;
    int i;
    int j;

    temp = data->map->map_tiles;
    i = 0;
    while (temp[i])
    {
        j = 0;
        while (temp[i][j])
        {
            if (temp[i][j] == '\t')
                return (ERROR);
            j++;
        }
        i++;
    }
    return (SUCCESS);
}
