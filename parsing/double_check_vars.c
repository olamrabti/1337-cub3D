/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_check_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:16:54 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/11 11:04:53 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_duplicated_vars(char *var, char *line)
{
    char *first_pos;
    char *next_pos;
    size_t var_len = ft_strlen(var);

    first_pos = ft_strnstr(line, var, ft_strlen(line));
    if (first_pos)
    {
        next_pos = ft_strnstr(first_pos + var_len, var, ft_strlen(line) - (first_pos + var_len - line));
        if (next_pos)
        {
            return ERROR;
        }
    }
    return SUCCESS;
}

int ft_missing_vars(char *var, char *line)
{
    if (ft_strnstr(line, var, ft_strlen(line)) == NULL)
    {
        printf("Missing variable: %s\n", var);
        return ERROR;
    }
    return SUCCESS;
}

int ft_double_check_vars(t_data *data)
{
    char *line;

    line = data->map->single_line_vars;
    if (ft_duplicated_vars("EA", line) == ERROR)
        return ERROR;
    if (ft_duplicated_vars("NO", line) == ERROR)
        return ERROR;
    if (ft_duplicated_vars("WE", line) == ERROR)
        return ERROR;
    if (ft_duplicated_vars("SO", line) == ERROR)
        return ERROR;
    if (ft_duplicated_vars("F", line) == ERROR)
        return ERROR;
    if (ft_duplicated_vars("C", line) == ERROR)
        return ERROR;
    if (ft_missing_vars("EA", line) == ERROR)
        return ERROR;
    if (ft_missing_vars("NO", line) == ERROR)
        return ERROR;
    if (ft_missing_vars("WE", line) == ERROR)
        return ERROR;
    if (ft_missing_vars("SO", line) == ERROR)
        return ERROR;
    if (ft_missing_vars("F", line) == ERROR)
        return ERROR;
    if (ft_missing_vars("C", line) == ERROR)
        return ERROR;
    return SUCCESS;
}
