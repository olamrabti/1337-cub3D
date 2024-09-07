/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_zero_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 03:45:48 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/07 10:53:01 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_src/cub3d_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_check_zero_surroundings(char **map, int i, int j)
{
	if (map[i][j + 1] == ' ' || map[i][j + 1] == '\0')
		return (ERROR);
	if (j > 0 && map[i][j - 1] == ' ')
		return (ERROR);
	if (map[i - 1][j] == ' ')
		return (ERROR);
	if (map[i + 1] && map[i + 1][j] == ' ')
		return (ERROR);
	return (SUCCESS);
}

int	ft_valide_map(t_map **map)
{
	char	**temp;
	int		i;
	int		j;

	temp = (*map)->map_tiles;
	if (ft_only_ones(temp[0]) == ERROR)
		return (ERROR);
	if (ft_only_ones(temp[(*map)->map_height - 1]) == ERROR)
		return (ERROR);
	if (ft_start_with_one(map) == ERROR)
		return (ERROR);
	i = 1;
	while (i < (*map)->map_height - 1)
	{
		j = 0;
		while (temp[i][j])
		{
			if (temp[i][j] == '0')
				if (ft_check_zero_surroundings(temp, i, j) == ERROR)
					return (ERROR);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
