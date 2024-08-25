/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:39:49 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/12 11:35:46 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_valide_rgb(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (!(ft_isdigit(str[i]) || str[i] == ','))
            return ERROR;
        i++;
    }
    return SUCCESS;
}

int ft_count_comma(char *str)
{
    int i = 0;
    int count = 0;
    while (str[i])
    {
        if (str[i] == ',')
            count++;
        i++;
    }
    if (count == 2)
        return SUCCESS;
    return ERROR;
}

int ft_parse_color(char *str, t_data *data)
{
    char **split;
    int i;

    if (!str)
        return ERROR;
    if (ft_valide_rgb(str) == SUCCESS && ft_count_comma(str) == SUCCESS)
    {
        split = ft_split(str, ',', data);
        i = 0;
        while (split[i])
        {
            // printf("split: %s\n", split[i]);
            if (ft_atoi(split[i]) > 255 || ft_atoi(split[i]) < 0)
                return ERROR;
            // free(split[i]);
            i++;
        }
        if (i < 3)
            return ERROR;
    }
    else
        return ERROR;
    return SUCCESS;    
}

int ft_check_vars(t_data *data)
{
    if (ft_parse_color(data->map->f_color, data) == ERROR)
        return ERROR;
    if (ft_parse_color(data->map->c_color, data) == ERROR)
        return ERROR;
    return (SUCCESS);
}
