/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 20:21:20 by oumimoun          #+#    #+#             */
/*   Updated: 2024/08/30 05:19:36 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(int i)
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

int	ft_parsing_suite(t_data *data)
{
	if (ft_has_tabs(data) == ERROR)
		return (ft_error(6), (ERROR));
	if (ft_check_players(data) == ERROR)
		return (ft_error(7), (ERROR));
	if (ft_save_player_pos(data) == ERROR)
		return (ft_error(-1), (ERROR));
	if (ft_fill_map_dimension(data) == ERROR)
		return ((ft_error(-1), (ERROR)));
	if (ft_fill_map_with_sp(data) == ERROR)
		return (((ft_error(-1), (ERROR))));
	if (ft_valide_map(data) == ERROR)
		return ((ft_error(8), (ERROR)));
	if (ft_stores_f_c(data) == ERROR)
		return (ft_error(-1), (ERROR));
	return (SUCCESS);
}

int	ft_parsing(char *map_path, t_data *data)
{
	if (ft_parse_map_path(map_path) == ERROR)
		return (ft_error(1), (ERROR));
	if (ft_parse_map_variables(map_path, data) == ERROR)
		return (ft_error(2), (ERROR));
	if (ft_double_check_vars(data) == ERROR)
		return (ft_error(3), (ERROR));
	if (ft_parsing_map(map_path, data) == ERROR)
		return (ft_error(-1), (ERROR));
	if (ft_save_vars(map_path, data) == ERROR)
		return (ft_error(-1), (ERROR));
	if (ft_check_vars(data) == ERROR)
		return (ft_error(5), (ERROR));
	if (ft_split_map(data) == ERROR)
		return (ft_error(-1), (ERROR));
	if (ft_parsing_suite(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
