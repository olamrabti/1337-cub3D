/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:25:51 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/24 19:18:47 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_fill_map_dimension(t_data *data)
{
    int i = 0;
    int max_width = 0;
    char **map;

    if (!data)
        return ERROR;
    map = data->map->map_tiles;
    while (map[i])
    {
        int line_length = ft_strlen(map[i]);
        if (line_length > max_width)
            max_width = line_length;
        i++;
    }
    if (i == 0)
        return ERROR;
    data->map->map_width = max_width;
    // printf("map_width:-->%d\n", data->map->map_width);
    data->map->map_height = i;
    // printf("map_height:-->%d\n", data->map->map_height);
    if (i > max_width)
        data->map->tile_size = WIDTH / i;
    else
        data->map->tile_size = HEIGHT / max_width;
    printf("tilesize:-->%d\n", data->map->tile_size);
    return SUCCESS;
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
    map = data->map->map_tiles;
    int i = 0;
    int j;
    while (map[i])
    {
        j = 0;
        while (map[i][j] == ' ')
            j++;
        if (map[i][j] != '1')
            return ERROR;
        i++;
    }
    return SUCCESS;
}

int ft_check_zero_surroundings(char **map, int i, int j)
{
    if (map[i][j + 1] == ' ' || map[i][j + 1] == '\0')
    {
        printf("1\n");
        return ERROR;
    }
    if (j > 0 && map[i][j - 1] == ' ')
    {
        printf("2\n");
        return ERROR;
    }
    if (map[i - 1][j] == ' ')
    {
        printf("i========|%d|\n", i - 1);
        printf("j ========|%d|\n", j);
        printf("===============|%c|\n", map[i - 1][j]);
        return ERROR;
    }
    if (map[i + 1] && map[i + 1][j] == ' ')
    {
        printf("4\n");
        return ERROR;
    }
    return SUCCESS;
}

int ft_valide_map(t_data *data)
{
    char **temp = data->map->map_tiles;
    int i, j;


    if (ft_only_ones(temp[0]) == ERROR)
        return ERROR;
    if (ft_only_ones(temp[data->map->map_height - 1]) == ERROR)
        return ERROR;


    if (ft_start_with_one(data) == ERROR)
        return ERROR;

    i = 1;
    while (i < data->map->map_height - 1)
    {
        j = 0;
        while (temp[i][j])
        {
            if (temp[i][j] == '0')
            {
                if (ft_check_zero_surroundings(temp, i, j) == ERROR)
                {
                    printf("===============|%c|\n", temp[i][j]);
                    printf("la asa7bi\n");
                    return ERROR;
                }
            }
            j++;
        }
        i++;
    }
    return SUCCESS;
}
