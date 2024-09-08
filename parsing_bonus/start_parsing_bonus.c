/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:21:20 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/08 11:16:02 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_src/cub3d_bonus.h"

int	ft_error_suite(int i)
{
	if (i == 9)
		return (ft_putstr_fd("Map doesn't have player\n", 2), exit(ERROR), 1);
	if (i == 10)
		return (ft_putstr_fd("Map has more than one player\n", 2), \
			exit(ERROR), 1);
	if (i == 11)
		return (ft_putstr_fd("Map should be surrounded by 1\n", 2), \
			exit(ERROR), 1);
	if (i == 12)
		return (ft_putstr_fd("Duplicated vars\n", 2), exit(ERROR), 1);
	if (i == 13)
		return (ft_putstr_fd("RGB should be between 0 and 255\n", 2), \
			exit(ERROR), 1);
	if (i == 14)
		return (ft_putstr_fd("Missing vars\n", 2), exit(ERROR), 1);
	return (0);
}

int	ft_error(int i)
{
	ft_putstr_fd("Error\n", 2);
	if (i == 1)
		return (ft_putstr_fd("Wrong path\n", 2), exit(ERROR), 1);
	if (i == 2)
		return (ft_putstr_fd("Map should end with .cub\n", 2), exit(ERROR), 1);
	if (i == 3)
		return (ft_putstr_fd("Name of vars isn't valide\n", 2), exit(ERROR), 1);
	if (i == 4)
		return (ft_putstr_fd("Random char in the map\n", 2), exit(ERROR), 1);
	if (i == 5)
		return (ft_putstr_fd("Map contains newline\n", 2), exit(ERROR), 1);
	if (i == 6)
		return (ft_putstr_fd("Not a valid RGB\n", 2), exit(ERROR), 1);
	if (i == 7)
		return (ft_putstr_fd("Empty map\n", 2), exit(ERROR), 1);
	if (i == 8)
		return (ft_putstr_fd("Map contains tabs\n", 2), exit(ERROR), 1);
	ft_error_suite(i);
	return (0);
}

int	ft_parsing_suite(t_map **map, t_addr **addr)
{
	if (ft_has_tabs(map) == ERROR)
		return (ERROR);
	if (ft_check_players(map) == ERROR)
		return (ERROR);
	if (ft_save_player_pos(map) == ERROR)
		return (ERROR);
	if (ft_fill_map_dimension(map) == ERROR)
		return ((ft_error(-1), (ERROR)));
	if (ft_fill_map_with_sp(map, addr) == ERROR)
		return (((ft_error(-1), (ERROR))));
	if (ft_valide_map(map) == ERROR)
		return ((ft_error(11), (ERROR)));
	if (ft_stores_f_c(map, addr) == ERROR)
		return (ft_error(-1), (ERROR));
	return (SUCCESS);
}

int	ft_parsing(char *map_path, t_map **map, t_addr **addr)
{
	if (ft_parse_map_path(map_path) == ERROR)
		return (ft_error(1), (ERROR));
	if (ft_parse_map_variables(map_path, map, addr) == ERROR)
		return (ft_error(2), (ERROR));
	if (ft_double_check_vars(map) == ERROR)
		return (ERROR);
	if (ft_parsing_map(map_path, map, addr) == ERROR)
		return (ERROR);
	if (ft_save_vars(map_path, map, addr) == ERROR)
		return (ft_error(-1), (ERROR));
	if (ft_check_vars(map, addr) == ERROR)
		return (ERROR);
	if (ft_split_map(map, addr) == ERROR)
		return (ERROR);
	if (ft_parsing_suite(map, addr) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
