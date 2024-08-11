/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:49:11 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/11 13:58:38 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_valid_char(char c)
{
    printf("%c",  c);
    if (c == '\n')
        return 1;
    if (c == '\t')
        return 1;
    if (c == ' ')
        return 1;
    if (c == '0')
        return 1;
    if (c == '1')
        return 1;
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

int ft_check_random_chars(char *line)
{
    int i = 0;

    while (line[i])
    {
        if (!ft_valid_char(line[i]))
        {
            printf("line[%d] = %d",i , line[i]);
            return (ERROR);
        }
        i++;
    }
    return SUCCESS;
}

char *ft_bring_map(int fd)
{
    char *line;
    line = get_next_line(fd);
    while (line)
    {
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if ((line[i] == '0' || line[i] == '1'))
            break;
        line = get_next_line(fd);
    }
    return line;
}

int ft_another_newline(char *str)
{
    int i = 0;

    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '\n')
    {
        i++;
        int j = i;
        while (str[j])
        {
            if (str[j] == '\n' || str[j] == ' ' || str[j] == '\t')
                j++;
            else
            {
                printf("str[%d] = %c", i, str[i]);
                return ERROR;
            }
        }
    }
    return SUCCESS;
}

int ft_check_newlines(char *single_line_map)
{
    int i = 0;
    while (single_line_map[i])
    {
        if (single_line_map[i] == '\n')
        {
            if (ft_another_newline(&single_line_map[i + 1]) == ERROR) // FIXME everything is wrong according to this func 
            {
                printf("klawi 2\n");
                return ERROR;
            }
        }
        i++;
    }
    return SUCCESS;
}

int ft_parsing_map(char *map_path, t_data *data)
{
    int fd;
    char *line;
    char *single_line_map;

    single_line_map = ft_strdup("");
    fd = open(map_path, O_RDONLY);
    if (fd < 0)
        return ERROR;
    data->map->map_height = 0;
    line = ft_bring_map(fd);
    while (line)
    {
        data->map->map_height++;
        single_line_map = ft_strjoin(single_line_map, line);
        line = get_next_line(fd);
    }
    if (ft_check_random_chars(single_line_map) == ERROR) // FIXME Doesnt do it's work 
        return ERROR;
    // printf("map:{%s}\n", single_line_map);
    if (ft_check_newlines(single_line_map) == ERROR) 
        return ERROR;
    data->map->single_line_map = single_line_map;
    close(fd);
    return SUCCESS;
}
