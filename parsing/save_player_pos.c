/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_player_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:27:09 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/11 14:53:59 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_is_player_direction(char c)
{
    if (c == 'N')
        return 1;
    if (c == 'S')
        return 1;
    if (c == 'E')
        return 1;
    if (c == 'W')
        return 1;
    return 0;
}

int ft_check_players(t_data *data)
{
    char **temp;
    int i;
    int j;
    int count;

    count  = 0;
    temp = data->map->map_tiles;
    i = 0;
    j = 0;
    while (temp[i])
    {
        // printf("tmp[%d] :%s\n",i, temp[i]);
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
        return ERROR;
    return SUCCESS;
}

int ft_save_player_pos(t_data *data)
{
    char **temp;
    int i;
    int j;

    temp = data->map->map_tiles;
    i = 0;
    j = 0;
    while (temp[i])
    {
        j = 0;
        while (temp[i][j])
        {
            if (ft_is_player_direction(temp[i][j]))
            {
                data->map->player_direction = temp[i][j];
                data->map->player_x = j; // changed this - 1
                data->map->player_y = i; // changed this
                temp[i][j] = '0';
                printf("player{%c}\n", temp[i][j]);
            }
            j++;
        }
        i++;
    }
    // printf("player_direction{%c}\n", data->map->player_direction);
    // printf("player_x{%d}\n", data->map->player_x);
    // printf("player_y{%d}\n", data->map->player_y);
    return SUCCESS;
}
