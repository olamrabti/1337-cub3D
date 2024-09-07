/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_vars_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:09:28 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/07 10:53:46 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_src/cub3d_bonus.h"

int	ft_extract_and_assign(char *line, int i, char **destination, t_addr **addr)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	*destination = gc_substr(line, i, ft_strlen(&line[i]) - 1, addr);
	return (SUCCESS);
}

void	ft_process_texture(char *line, int i, t_map **map, t_addr **addr)
{
	if (ft_strncmp(&line[i], "NO", 2) == 0)
		ft_extract_and_assign(line, i + 2, &((*map)->no_texture_path), addr);
	else if (ft_strncmp(&line[i], "SO", 2) == 0)
		ft_extract_and_assign(line, i + 2, &((*map)->so_texture_path), addr);
	else if (ft_strncmp(&line[i], "WE", 2) == 0)
		ft_extract_and_assign(line, i + 2, &((*map)->we_texture_path), addr);
	else if (ft_strncmp(&line[i], "EA", 2) == 0)
		ft_extract_and_assign(line, i + 2, &((*map)->ea_texture_path), addr);
	else if (ft_strncmp(&line[i], "F", 1) == 0)
		ft_extract_and_assign(line, i + 1, &((*map)->f_color), addr);
	else if (ft_strncmp(&line[i], "C", 1) == 0)
		ft_extract_and_assign(line, i + 1, &((*map)->c_color), addr);
}

void	ft_process_line(char *line, t_map **map, t_addr **addr)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n')
		return ;
	if (ft_valide_wall_direction(&line[i]) == SUCCESS)
		ft_process_texture(line, i, map, addr);
}

int	ft_save_vars(char *map_path, t_map **map, t_addr **addr)
{
	char	*line;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (ERROR);
	line = get_next_line(fd, addr);
	while (line)
	{
		ft_process_line(line, map, addr);
		if (line[0] == '0' || line[0] == '1')
			break ;
		line = get_next_line(fd, addr);
	}
	close(fd);
	return (SUCCESS);
}

char	*ft_bring_map(int fd, t_addr **addr)
{
	char	*line;
	int		i;

	line = get_next_line(fd, addr);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if ((line[i] == '0' || line[i] == '1'))
			break ;
		line = get_next_line(fd, addr);
	}
	return (line);
}
