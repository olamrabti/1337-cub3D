/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:09:28 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/11 10:46:22 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_save_vars(char *map_path, t_data *data)
{
    int fd;
    char *line;

    fd = open(map_path, O_RDONLY);
    if (fd < 0)
        return ERROR;
    
    line = get_next_line(fd);
    while (line)
    {
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if (line[i] == '\n')
        {
            line = get_next_line(fd);
            continue;
        }
        if (line[i] == '0' || line[i] == '1')
            break;
        if (ft_valide_wall_direction(&line[i]) == SUCCESS)
        {
            if (ft_strncmp(&line[i], "NO", 2) == 0)
            {
                i+=2;
                while (line[i] == ' ' || line[i] == '\t')
                    i++;
                data->map->no_texture_path =  ft_substr(line, i, ft_strlen(&line[i]) - 1);
                printf("|%s|\n", data->map->no_texture_path);
            }
            if (ft_strncmp(&line[i], "SO", 2) == 0)
            {
                i+=2;
                while (line[i] == ' ' || line[i] == '\t')
                    i++;
                data->map->so_texture_path =  ft_substr(line, i, ft_strlen(&line[i]) - 1);
                printf("|%s|\n", data->map->so_texture_path);
            }
            if (ft_strncmp(&line[i], "WE", 2) == 0)
            {
                i+=2;
                while (line[i] == ' ' || line[i] == '\t')
                    i++;
                data->map->we_texture_path =  ft_substr(line, i, ft_strlen(&line[i]) - 1);
                printf("|%s|\n", data->map->we_texture_path);
            }
            if (ft_strncmp(&line[i], "EA", 2) == 0)
            {
                i+=2;
                while (line[i] == ' ' || line[i] == '\t')
                    i++;
                data->map->ea_texture_path =  ft_substr(line, i, ft_strlen(&line[i]) - 1);
                printf("|%s|\n", data->map->ea_texture_path);
            }
            if (ft_strncmp(&line[i], "F", 1) == 0)
            {
                i++;
                while (line[i] == ' ' || line[i] == '\t')
                    i++;
                data->map->f_color =  ft_substr(line, i, ft_strlen(&line[i]) - 1);
                printf("|%s|\n", data->map->f_color);
            }
            if (ft_strncmp(&line[i], "C", 1) == 0)
            {
                i++;
                while (line[i] == ' ' || line[i] == '\t')
                    i++;
                data->map->c_color =  ft_substr(line, i, ft_strlen(&line[i]) - 1);
                printf("|%s|\n", data->map->c_color);
            }
        }
        line = get_next_line(fd);
    }
    close(fd);
    return SUCCESS;
}
