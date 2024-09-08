/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:39:49 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/08 11:01:02 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_valide_rgb(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i]) || str[i] == ',' || str[i] == ' '))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	ft_count_comma(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count == 2)
		return (SUCCESS);
	return (ERROR);
}

int	ft_parse_color(char *str, t_addr **addr)
{
	char	**split;
	int		i;

	if (!str)
		return (ERROR);
	if (ft_valide_rgb(str) == SUCCESS && ft_count_comma(str) == SUCCESS)
	{
		split = ft_split(str, ',', addr);
		i = 0;
		while (split[i])
		{
			if (ft_all_spaces(split[i]) == 1 || ft_strcmp(split[i], "") == 0)
				return (ft_error(6), (ERROR));
			if (ft_atoi(split[i]) > 255 || ft_atoi(split[i]) < 0)
				return (ft_error(13), (ERROR));
			i++;
		}
		if (i < 3)
			return (ft_error(6), (ERROR));
	}
	else
		return (ft_error(6), (ERROR));
	return (SUCCESS);
}

int	ft_check_vars(t_map **map, t_addr **addr)
{
	if (ft_parse_color((*map)->f_color, addr) == ERROR)
		return (ERROR);
	if (ft_parse_color((*map)->c_color, addr) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
