/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:21:20 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/02 10:15:42 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_src/cub3d_bonus.h"

void ft_error(int i)
{
	ft_putstr_fd("Error\n", 2);
	if (i == 1)
		ft_putstr_fd("Wrong path\n", 2);
	if (i == 2)
		ft_putstr_fd("Wrong map parameters\n", 2);
	if (i == 3)
		ft_putstr_fd("Missing variables\n", 2);
	if (i == 4)
		ft_putstr_fd("Duplicated variables\n", 2);
	if (i == 5)
		ft_putstr_fd("Wrong color parametres\n", 2);
	if (i == 6)
		ft_putstr_fd("Map contains tabs\n", 2);
	if (i == 7)
		ft_putstr_fd("Wrong player direction\n", 2);
	if (i == 8)
		ft_putstr_fd("Map is not valid\n", 2);
	exit(ERROR);
}

int ft_parsing_suite(t_map **map , t_addr **addr)
{
	if (ft_has_tabs(map) == ERROR)
		return (ft_error(6), (ERROR));
	if (ft_check_players(map) == ERROR)
		return (ft_error(7), (ERROR));
	if (ft_save_player_pos(map) == ERROR)
		return (ft_error(-1), (ERROR));
	if (ft_fill_map_dimension(map) == ERROR)
		return ((ft_error(-1), (ERROR)));
	if (ft_fill_map_with_sp(map, addr) == ERROR)
		return (((ft_error(-1), (ERROR))));
	if (ft_valide_map(map) == ERROR)
		return ((ft_error(8), (ERROR)));
	if (ft_stores_f_c(map, addr) == ERROR)
		return (ft_error(-1), (ERROR));
	return (SUCCESS);
}

int ft_parsing(char *map_path, t_map **map, t_addr **addr)
{
	if (ft_parse_map_path(map_path) == ERROR)
		return (ft_error(1), (ERROR));
	if (ft_parse_map_variables(map_path, map, addr) == ERROR)
		return (ft_error(2), (ERROR));
	if (ft_double_check_vars(map) == ERROR)
		return (ft_error(3), (ERROR));
	if (ft_parsing_map(map_path, map, addr) == ERROR)
		return (ft_error(-1), (ERROR));
	if (ft_save_vars(map_path, map, addr) == ERROR)
		return (ft_error(-1), (ERROR));
	if (ft_check_vars(map, addr) == ERROR)
		return (ft_error(5), (ERROR));
	if (ft_split_map(map, addr) == ERROR)
		return (ft_error(-1), (ERROR));
	if (ft_parsing_suite(map, addr) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
