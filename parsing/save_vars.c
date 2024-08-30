/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:09:28 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/30 05:14:55 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_extract_and_assign(char *line, int i, char **destination, t_data *data)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	*destination = gc_substr(line, i, ft_strlen(&line[i]) - 1, &data->addr);
	return (SUCCESS);
}

void	ft_process_texture(char *line, int i, t_data *data)
{
	if (ft_strncmp(&line[i], "NO", 2) == 0)
		ft_extract_and_assign(line, i + 2, &(data->map->no_texture_path), data);
	else if (ft_strncmp(&line[i], "SO", 2) == 0)
		ft_extract_and_assign(line, i + 2, &(data->map->so_texture_path), data);
	else if (ft_strncmp(&line[i], "WE", 2) == 0)
		ft_extract_and_assign(line, i + 2, &(data->map->we_texture_path), data);
	else if (ft_strncmp(&line[i], "EA", 2) == 0)
		ft_extract_and_assign(line, i + 2, &(data->map->ea_texture_path), data);
	else if (ft_strncmp(&line[i], "F", 1) == 0)
		ft_extract_and_assign(line, i + 1, &(data->map->f_color), data);
	else if (ft_strncmp(&line[i], "C", 1) == 0)
		ft_extract_and_assign(line, i + 1, &(data->map->c_color), data);
}

void	ft_process_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n')
		return ;
	if (ft_valide_wall_direction(&line[i]) == SUCCESS)
		ft_process_texture(line, i, data);
}

int	ft_save_vars(char *map_path, t_data *data)
{
	char	*line;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (ERROR);
	line = get_next_line(fd, data);
	while (line)
	{
		ft_process_line(line, data);
		if (line[0] == '0' || line[0] == '1')
			break ;
		line = get_next_line(fd, data);
	}
	close(fd);
	return (SUCCESS);
}

char	*ft_bring_map(int fd, t_data *data)
{
	char	*line;
	int		i;

	line = get_next_line(fd, data);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if ((line[i] == '0' || line[i] == '1'))
			break ;
		line = get_next_line(fd, data);
	}
	return (line);
}
