/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:23:46 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/11 13:59:52 by olamrabt         ###   ########.fr       */
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
    data->map->map_tiles = ft_split(data->map->single_line_map, '\n');
    if (!data->map->map_tiles)
        return ERROR;
    int i = 0;
    char **temp = data->map->map_tiles;
    while (temp[i])
    {
        if (ft_all_spaces(temp[i]))
        {
            free(temp[i]);
            temp[i] = NULL;
        }
        i++;
    }
    return SUCCESS;
}

int ft_has_tabs(t_data *data)
{
    char **temp;

    temp = data->map->map_tiles;
    int i = 0;
    int j;
    while (temp[i])
    {
        j = 0;
        // printf("[%s]\n", temp[i]);
        while (temp[i][j])
        {
            if (temp[i][j] == '\t')
            {
                puts("here");
                printf("---%c--\n", temp[i][j]);
                return ERROR;
            }
            j++;
        }
        i++;
    }
    return SUCCESS;
}
