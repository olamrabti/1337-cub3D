/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_player_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:27:09 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/12 09:10:17 by oumimoun         ###   ########.fr       */
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
                data->map->player_x = j;
                data->map->player_y = i; 
                temp[i][j] = '0';
            }
            j++;
        }
        i++;
    }
    return SUCCESS;
}
