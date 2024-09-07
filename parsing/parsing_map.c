/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:49:11 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/07 10:41:45 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_valid_char(char c)
{
	if (c == '\n')
		return (1);
	if (c == '\t')
		return (1);
	if (c == ' ')
		return (1);
	if (c == '0')
		return (1);
	if (c == '1')
		return (1);
	if (c == 'N')
		return (1);
	if (c == 'S')
		return (1);
	if (c == 'E')
		return (1);
	if (c == 'W')
		return (1);
	return (0);
}

int	ft_check_random_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_valid_char(line[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	ft_another_newline(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\n')
	{
		i++;
		j = i;
		while (str[j])
		{
			if (str[j] == '\n' || str[j] == ' ' || str[j] == '\t')
				j++;
			else
				return (ERROR);
		}
	}
	return (SUCCESS);
}

int	ft_check_newlines(char *single_line_map)
{
	int	i;

	i = 0;
	while (single_line_map[i])
	{
		if (single_line_map[i] == '\n')
		{
			if (ft_another_newline(&single_line_map[i + 1]) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_parsing_map(char *map_path, t_map **map, t_addr **addr)
{
	char		*single_line_map;
	char		*line;
	int			fd;

	single_line_map = gc_strdup("", addr);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (ERROR);
	(*map)->map_height = 0;
	line = ft_bring_map(fd, addr);
	while (line)
	{
		(*map)->map_height++;
		single_line_map = gc_strjoin(single_line_map, line, addr);
		line = get_next_line(fd, addr);
	}
	if (ft_check_random_chars(single_line_map) == ERROR)
		return (ft_error(4), (ERROR));
	if (ft_check_newlines(single_line_map) == ERROR)
		return (ft_error(5), (ERROR));
	(*map)->single_line_map = single_line_map;
	close(fd);
	return (SUCCESS);
}
