/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stores_f_c_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 03:32:42 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/07 10:53:57 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_src/cub3d_bonus.h"

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
			return (ft_error(2), (ERROR));
	}
	else
		if (ft_strcmp(ft_strchr(map_path, '.'), ".cub"))
			return (ft_error(2), (ERROR));
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

int	ft_read_map_lines(int fd, char **single_line_vars, t_addr **addr)
{
	char	*line;
	int		i;

	line = get_next_line(fd, addr);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n')
		{
			line = get_next_line(fd, addr);
			continue ;
		}
		if (line[i] == '0' || line[i] == '1')
			break ;
		if (ft_valide_wall_direction(&line[i]) == ERROR)
			return (ft_error(3), (ERROR));
		*single_line_vars = gc_strjoin(*single_line_vars, line, addr);
		line = get_next_line(fd, addr);
	}
	return (SUCCESS);
}

int	ft_parse_map_variables(char *map_path, t_map **map, t_addr **addr)
{
	int		fd;
	char	*single_line_vars;

	single_line_vars = gc_strdup("", addr);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (ERROR);
	if (ft_read_map_lines(fd, &single_line_vars, addr) == ERROR)
		return (close(fd), ERROR);
	(*map)->single_line_vars = single_line_vars;
	close(fd);
	return (SUCCESS);
}

int	ft_stores_f_c(t_map **map, t_addr **addr)
{
	char	**split;
	int		i;

	split = ft_split((*map)->f_color, ',', addr);
	(*map)->f_rgb = safe_alloc(addr, 3, sizeof(int));
	i = 0;
	while (split[i])
	{
		(*map)->f_rgb[i] = ft_atoi(split[i]);
		i++;
	}
	split = ft_split((*map)->c_color, ',', addr);
	(*map)->c_rgb = safe_alloc(addr, 3, sizeof(int));
	i = 0;
	while (split[i])
	{
		(*map)->c_rgb[i] = ft_atoi(split[i]);
		i++;
	}
	return (SUCCESS);
}
