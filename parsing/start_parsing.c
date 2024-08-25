 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:21:20 by oumimoun          #+#    #+#             */
/*   Updated: 2024/07/25 14:16:39 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int ft_parse_map_path(char *map_path)
{
    int fd;

    fd = open(map_path, O_RDONLY);
    if (fd < 0)
        return (ft_putstr_fd("Error\nWrong path\n", 2), ERROR);
    close(fd);
    if (map_path[0] == '.')
    {
        if (ft_strcmp(ft_strchr((map_path + 1), '.'), ".cub"))
            return (ft_putstr_fd("Error\npath should end with \".cub\"\n", 2), ERROR);
    }
    else
    {
        if (ft_strcmp(ft_strchr(map_path, '.'), ".cub"))
            return (ft_putstr_fd("Error\npath should end with \".cub\"\n", 2), ERROR);
    }
    return (SUCCESS);
}

int ft_valide_wall_direction(char *line)
{
    if ((ft_strncmp(line, "NO", 2) == 0) && line[2] == ' ')
        return SUCCESS;
    if (ft_strncmp(line, "SO", 2) == 0 && line[2] == ' ')
        return SUCCESS;
    if (ft_strncmp(line, "WE", 2) == 0 && line[2] == ' ')
        return SUCCESS;
    if (ft_strncmp(line, "EA", 2) == 0 && line[2] == ' ')
        return SUCCESS;
    if (ft_strncmp(line, "F", 1) == 0 && line[1] == ' ')
        return SUCCESS;
    if (ft_strncmp(line, "C", 1) == 0 && line[1] == ' ')
        return SUCCESS;
    return (ERROR);
}

int ft_parsing_vars(char *map_path, t_data *data)
{
    int fd;
    char *line;
    char *single_line_vars;

    single_line_vars = gc_strdup("", &data->addr);
    fd = open(map_path, O_RDONLY);
    if (fd < 0)
        return (ERROR);
    line = get_next_line(fd, data);
    while (line)
    {
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if (line[i] == '\n')
        {
            line = get_next_line(fd, data);
            continue;
        }
        if (line[i] == '0' || line[i] == '1')
            break;
        if (ft_valide_wall_direction(&line[i]) == ERROR)
            return ft_putstr_fd("Error\nwrong map parameters\n", 2), ERROR;
        single_line_vars = gc_strjoin(single_line_vars, line, &data->addr);
        line = get_next_line(fd, data);
    }
    data->map->single_line_vars = single_line_vars;
    close(fd);
    return SUCCESS;
}

int ft_parsing(char *map_path, t_data *data)
{
    if (ft_parse_map_path(map_path) == ERROR)
        return (ERROR);
    if (ft_parsing_vars(map_path, data) == ERROR)
        return (ERROR);
    if (ft_double_check_vars(data) == ERROR)
        return ERROR;
    if (ft_parsing_map(map_path, data) == ERROR)
        return ERROR;
    if (ft_save_vars(map_path, data) == ERROR)
        return ERROR;
    if (ft_check_vars(data) == ERROR)
        return ERROR;
    if (ft_split_map(data) == ERROR)
        return ERROR;
    if (ft_has_tabs(data) == ERROR)
        return ERROR;
    if (ft_check_players(data) == ERROR)
        return ERROR;
    if (ft_save_player_pos(data) == ERROR)
        return ERROR;
    if (ft_fill_map_dimension(data) == ERROR)
        return ERROR;
    if (ft_fill_map_with_sp(data) == ERROR)
        return ERROR;
    if (ft_valide_map(data) == ERROR)
        return ERROR;
    return SUCCESS;
}
