/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stores_f_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 03:32:42 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/30 16:00:39 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_parse_map_path(char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (ERROR);
	close(fd);
	if (map_path[0] == '.')
	{
		if (ft_strcmp(ft_strchr((map_path + 1), '.'), ".cub"))
			return (ERROR);
	}
	else
		if (ft_strcmp(ft_strchr(map_path, '.'), ".cub"))
			return (ERROR);
	return (SUCCESS);
}

int	ft_valide_wall_direction(char *line)
{
	if ((ft_strncmp(line, "NO", 2) == 0) && line[2] == ' ')
		return (SUCCESS);
	if (ft_strncmp(line, "SO", 2) == 0 && line[2] == ' ')
		return (SUCCESS);
	if (ft_strncmp(line, "WE", 2) == 0 && line[2] == ' ')
		return (SUCCESS);
	if (ft_strncmp(line, "EA", 2) == 0 && line[2] == ' ')
		return (SUCCESS);
	if (ft_strncmp(line, "F", 1) == 0 && line[1] == ' ')
		return (SUCCESS);
	if (ft_strncmp(line, "C", 1) == 0 && line[1] == ' ')
		return (SUCCESS);
	return (ERROR);
}

int	ft_read_map_lines(int fd, t_data *data, char **single_line_vars)
{
	char	*line;
	int		i;

	line = get_next_line(fd, data);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n')
		{
			line = get_next_line(fd, data);
			continue ;
		}
		if (line[i] == '0' || line[i] == '1')
			break ;
		if (ft_valide_wall_direction(&line[i]) == ERROR)
			return (ERROR);
		*single_line_vars = gc_strjoin(*single_line_vars, line, &data->addr);
		line = get_next_line(fd, data);
	}
	return (SUCCESS);
}

int	ft_parse_map_variables(char *map_path, t_data *data)
{
	int		fd;
	char	*single_line_vars;

	single_line_vars = gc_strdup("", &data->addr);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (ERROR);
	if (ft_read_map_lines(fd, data, &single_line_vars) == ERROR)
		return (close(fd), ERROR);
	data->map->single_line_vars = single_line_vars;
	close(fd);
	return (SUCCESS);
}

int	ft_stores_f_c(t_data *data)
{
	char	**split;
	int		i;

	split = ft_split(data->map->f_color, ',', data);
	data->map->f_rgb = safe_alloc(&data->addr, 3, sizeof(int));
	i = 0;
	while (split[i])
	{
		data->map->f_rgb[i] = ft_atoi(split[i]);
		i++;
	}
	split = ft_split(data->map->c_color, ',', data);
	data->map->c_rgb = safe_alloc(&data->addr, 3, sizeof(int));
	i = 0;
	while (split[i])
	{
		data->map->c_rgb[i] = ft_atoi(split[i]);
		i++;
	}
	return (SUCCESS);
}
