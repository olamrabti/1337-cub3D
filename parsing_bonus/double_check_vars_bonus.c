/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_check_vars_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:16:54 by oumimoun          #+#    #+#             */
/*   Updated: 2024/09/07 10:53:06 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_src/cub3d_bonus.h"

int	ft_duplicated_vars(char *var, char *line)
{
	char	*first_pos;
	char	*next_pos;
	size_t	var_len;

	var_len = ft_strlen(var);
	first_pos = ft_strnstr(line, var, ft_strlen(line));
	if (first_pos)
	{
		next_pos = ft_strnstr(first_pos + var_len, var, \
			ft_strlen(line) - (first_pos + var_len - line));
		if (next_pos)
			return (ft_error(12), (ERROR));
	}
	return (SUCCESS);
}

int	ft_missing_vars(char *var, char *line)
{
	if (ft_strnstr(line, var, ft_strlen(line)) == NULL)
		return (ft_error(14), (ERROR));
	return (SUCCESS);
}

int	ft_double_check_vars_suite(t_map **map)
{
	char	*line;

	line = (*map)->single_line_vars;
	if (ft_missing_vars("EA", line) == ERROR)
		return (ERROR);
	if (ft_missing_vars("NO", line) == ERROR)
		return (ERROR);
	if (ft_missing_vars("WE", line) == ERROR)
		return (ERROR);
	if (ft_missing_vars("SO", line) == ERROR)
		return (ERROR);
	if (ft_missing_vars("F", line) == ERROR)
		return (ERROR);
	if (ft_missing_vars("C", line) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ft_double_check_vars(t_map **map)
{
	char	*line;

	line = (*map)->single_line_vars;
	if (ft_duplicated_vars("EA", line) == ERROR)
		return (ERROR);
	if (ft_duplicated_vars("NO", line) == ERROR)
		return (ERROR);
	if (ft_duplicated_vars("WE", line) == ERROR)
		return (ERROR);
	if (ft_duplicated_vars("SO", line) == ERROR)
		return (ERROR);
	if (ft_duplicated_vars("F", line) == ERROR)
		return (ERROR);
	if (ft_duplicated_vars("C", line) == ERROR)
		return (ERROR);
	if (ft_double_check_vars_suite(map) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
